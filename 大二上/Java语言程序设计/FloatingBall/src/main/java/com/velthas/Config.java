package com.velthas;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Properties;

public class Config {
    private static final Properties properties = new Properties();

    static {
        // 尝试从程序运行目录加载配置文件
        try (InputStream input = new FileInputStream("config.properties")) {
            properties.load(input);
        } catch (Exception e) {
            System.out.println("警告: 未找到 config.properties 文件，请在程序同目录下创建。将使用空 API Keys。");
            // 在这里可以设置默认值或提示用户
            properties.setProperty("DASHSCOPE_API_KEY", "");
            properties.setProperty("HF_API_TOKEN", "");
        }
    }

    public static String getAliyunApiKey() {
        return properties.getProperty("DASHSCOPE_API_KEY", ""); // 第二个参数是默认值
    }

    public static String getHuggingFaceApiKey() {
        return properties.getProperty("HF_API_TOKEN", "");
    }
}