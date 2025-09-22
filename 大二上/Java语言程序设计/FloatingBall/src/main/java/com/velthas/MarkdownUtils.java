package com.velthas;

import org.commonmark.node.*;
import org.commonmark.parser.Parser;
import org.commonmark.renderer.html.HtmlRenderer;
import org.commonmark.ext.gfm.tables.TablesExtension;
import org.commonmark.ext.autolink.AutolinkExtension;
import org.commonmark.ext.task.list.items.TaskListItemsExtension;
import java.util.Arrays;

/**
 * Markdown工具类，提供完善的Markdown解析和渲染功能
 */
public class MarkdownUtils {
    private static final Parser parser;
    private static final HtmlRenderer renderer;
    public static final String CSS_STYLE = """
        <style>
            body { font-family: 'Microsoft YaHei', 'Arial', sans-serif; margin: 0; padding: 8px; line-height: 1.6; }
            h1, h2, h3, h4, h5, h6 { color: #333; margin-top: 1.5em; margin-bottom: 0.5em; }
            p { margin: 1em 0; }
            a { color: #1a73e8; text-decoration: none; }
            a:hover { text-decoration: underline; }
            code { font-family: 'Consolas', 'Monaco', monospace; background-color: #f5f5f5; padding: 2px 4px; border-radius: 3px; }
            pre { background-color: #f5f5f5; padding: 12px; border-radius: 5px; overflow-x: auto; }
            pre code { background-color: transparent; padding: 0; }
            blockquote { border-left: 4px solid #ddd; padding-left: 16px; margin: 1em 0; color: #666; }
            table { border-collapse: collapse; width: 100%; margin: 1em 0; }
            th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
            th { background-color: #f2f2f2; }
            tr:nth-child(even) { background-color: #f9f9f9; }
            ul, ol { margin: 1em 0; padding-left: 2em; }
            img { max-width: 100%; height: auto; }
            .task-list-item { list-style-type: none; }
            .task-list-item-checkbox { margin-right: 0.5em; }
        </style>
    """;

    static {
        // 初始化带有扩展的解析器和渲染器
        parser = Parser.builder()
                .extensions(Arrays.asList(
                        TablesExtension.create(),
                        AutolinkExtension.create(),
                        TaskListItemsExtension.create()
                ))
                .build();

        renderer = HtmlRenderer.builder()
                .extensions(Arrays.asList(
                        TablesExtension.create(),
                        AutolinkExtension.create(),
                        TaskListItemsExtension.create()
                ))
                .build();
    }

    /**
     * 将Markdown文本转换为HTML
     * @param markdown Markdown文本
     * @return 转换后的HTML文本
     */
    public static String markdownToHtml(String markdown) {
        if (markdown == null || markdown.trim().isEmpty()) {
            return "";
        }

        Node document = parser.parse(markdown);
        // commonmark renderer会负责内部内容的HTML转义，防止XSS攻击
        return renderer.render(document);
    }

    /**
     * 将Markdown文本转换为完整的HTML文档（包含样式）
     * @param markdown Markdown文本
     * @return 完整的HTML文档
     */
    public static String markdownToHtmlDocument(String markdown) {
        String content = markdownToHtml(markdown);
        return "<!DOCTYPE html><html><head>" + CSS_STYLE + "</head><body>" + content + "</body></html>";
    }

    /**
     * 为聊天窗口准备HTML内容 (已修改，不再提前进行全局HTML转义)
     * 对于AI的Markdown回复，直接渲染Markdown。
     * 对于用户输入，可能需要额外考虑是否也支持Markdown，否则只进行HTML转义。
     * 在 AIChatWindow 中，我们已将 AI 和用户消息分开处理。
     * @param markdown Markdown文本
     * @return 适合聊天窗口显示的HTML
     */
    public static String prepareChatHtml(String markdown) {
        // 此方法现在直接调用markdownToHtml，因为它假设输入已经是Markdown
        // 外部调用者(AIChatWindow)负责判断是否需要先转义。
        return markdownToHtml(markdown);
    }

    /**
     * HTML转义，防止XSS攻击 (保留此方法供纯文本转义使用)
     * @param s 原始字符串
     * @return 转义后的字符串
     */
    public static String escapeHtml(String s) {
        if (s == null) {
            return "";
        }
        return s.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace("\"", "&quot;")
                .replace("'", "&#39;");
    }
}