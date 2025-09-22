package com.velthas;

import com.alibaba.dashscope.common.Message;
import com.alibaba.dashscope.common.Role;
import javax.swing.*;
import javax.swing.text.html.HTMLDocument;
import javax.swing.text.html.HTMLEditorKit;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AIChatWindow extends JDialog {

    private final JEditorPane chatPane;
    private final JTextField inputField;
    private final JButton backendButton;

    private final Map<String, AIClient> clients = new HashMap<>();
    private AIClient currentClient;

    private final List<Message> conversationHistory = new ArrayList<>();

    private boolean showOnLeft = false;

    public AIChatWindow() {
        super((Frame) null, "AI 对话", false);

        setSize(400, 400);
        setLayout(new BorderLayout());
        setAlwaysOnTop(true);
        setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE); // 当点击X时销毁对话框

        chatPane = new JEditorPane();
        chatPane.setEditorKit(new HTMLEditorKit());
        chatPane.setContentType("text/html");
        chatPane.setEditable(false);
        try {
            HTMLDocument doc = (HTMLDocument) chatPane.getDocument();
            doc.setAsynchronousLoadPriority(-1);
            chatPane.setText("<html><head>" + MarkdownUtils.CSS_STYLE + "</head><body></body></html>");
        } catch (Exception e) {
            e.printStackTrace();
            chatPane.setText("<html><head><style>body{font-family:Arial,sans-serif;}</style></head><body></body></html>");
        }
        JScrollPane scrollPane = new JScrollPane(chatPane);
        inputField = new JTextField();
        backendButton = new JButton("选择后端");
        JPanel bottomPanel = new JPanel(new BorderLayout());
        bottomPanel.add(backendButton, BorderLayout.WEST);
        bottomPanel.add(inputField, BorderLayout.CENTER);
        add(scrollPane, BorderLayout.CENTER);
        add(bottomPanel, BorderLayout.SOUTH);

        String aliyunKey = Config.getAliyunApiKey(); // 使用 Config 类获取 Key
        String hfKey = Config.getHuggingFaceApiKey(); // 使用 Config 类获取 Key
        AIClient aliyunClient = new AliyunClient(aliyunKey);
        AIClient hfClient = new HuggingFaceClient(hfKey);
        clients.put(aliyunClient.getName(), aliyunClient);
        clients.put(hfClient.getName(), hfClient);
        currentClient = (aliyunKey != null && !aliyunKey.isEmpty()) ? aliyunClient : hfClient;
        backendButton.setText(currentClient.getName());

        initializeConversation();

        backendButton.addActionListener(e -> showBackendMenu());
        inputField.addActionListener(e -> sendMessage());
    }

    // NEW: 清除对话记录并重新初始化
    public void startNewConversation() {
        SwingUtilities.invokeLater(() -> {
            initializeConversation(); // 清空历史记录并添加系统消息
            // 清空 JEditorPane 的显示内容
            try {
                chatPane.setText("<html><head>" + MarkdownUtils.CSS_STYLE + "</head><body></body></html>");
            } catch (Exception e) {
                e.printStackTrace();
                chatPane.setText("<html><head><style>body{font-family:Arial,sans-serif;}</style></head><body></body></html>");
            }
            chatPane.setCaretPosition(0); // 滚动到顶部
        });
    }

    private void initializeConversation() {
        conversationHistory.clear();
        conversationHistory.add(Message.builder()
                .role(Role.SYSTEM.getValue())
                .content("你是一个有帮助的 AI 助手。")
                .build());
    }

    private void showBackendMenu() {
        JPopupMenu menu = new JPopupMenu();
        for (String name : clients.keySet()) {
            JMenuItem item = new JMenuItem(name);
            item.addActionListener(e -> {
                currentClient = clients.get(name);
                backendButton.setText(currentClient.getName());
            });
            menu.add(item);
        }
        menu.show(backendButton, 0, backendButton.getHeight());
    }

    private void sendMessage() {
        String msg = inputField.getText().trim();
        if (msg.isEmpty()) return;

        appendMessage("你", msg, false);
        inputField.setText("");

        conversationHistory.add(Message.builder()
                .role(Role.USER.getValue())
                .content(msg)
                .build());

        new Thread(() -> {
            String reply;
            try {
                reply = currentClient.getReply(conversationHistory);
            } catch (Exception e) {
                reply = "请求失败：" + e.getMessage();
                e.printStackTrace();
            }
            final String finalReply = reply;

            conversationHistory.add(Message.builder()
                    .role(Role.ASSISTANT.getValue())
                    .content(finalReply)
                    .build());

            SwingUtilities.invokeLater(() -> {
                appendMessage(currentClient.getName(), finalReply, true);
            });
        }).start();
    }

    private void appendMessage(String sender, String content, boolean isAI) {
        SwingUtilities.invokeLater(() -> {
            try {
                String messageContentHtml = isAI ?
                        MarkdownUtils.markdownToHtml(content) :
                        MarkdownUtils.escapeHtml(content);

                String style = isAI ?
                        "background-color: #f5f5f5; padding: 8px; border-radius: 5px;" :
                        "margin: 8px 0;";

                String messageHtml = "<div style='" + style + "'><b>" + sender + ":</b> " + messageContentHtml + "</div><br>";

                HTMLEditorKit kit = (HTMLEditorKit) chatPane.getEditorKit();
                HTMLDocument doc = (HTMLDocument) chatPane.getDocument();
                kit.insertHTML(doc, doc.getLength(), messageHtml, 0, 0, null);

                chatPane.setCaretPosition(doc.getLength());
            } catch (Exception e) {
                e.printStackTrace();
                appendHtml("<div><b>" + sender + ":</b> " + MarkdownUtils.escapeHtml(content) + "</div><br>");
            }
        });
    }

    private void appendHtml(String html) {
        SwingUtilities.invokeLater(() -> {
            try {
                HTMLEditorKit kit = (HTMLEditorKit) chatPane.getEditorKit();
                HTMLDocument doc = (HTMLDocument) chatPane.getDocument();
                kit.insertHTML(doc, doc.getLength(), html, 0, 0, null);
                chatPane.setCaretPosition(doc.getLength());
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public void followBall(int ballX, int ballY, int ballSize) {
        if (!isVisible()) return;
        Rectangle screen = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
        int x, y = ballY;
        if (showOnLeft) {
            x = ballX - getWidth() - 10;
            if (x < screen.x) {
                x = ballX + ballSize + 10;
                showOnLeft = false;
            }
        } else {
            x = ballX + ballSize + 10;
            if (x + getWidth() > screen.x + screen.width) {
                x = ballX - getWidth() - 10;
                showOnLeft = true;
            }
        }
        setLocation(x, y);
    }
}