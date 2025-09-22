package com.velthas;

import com.alibaba.dashscope.common.Message; // 导入Message类
import com.alibaba.dashscope.common.Role;
import okhttp3.*;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.util.List; // 导入List

public class HuggingFaceClient implements AIClient {

    private static final String MODEL = "gpt2"; // 可换成其他公开模型
    private static final String API_URL = "https://api-inference.huggingface.co/models/" + MODEL;

    private final String apiKey;
    private final OkHttpClient client;
    private final ObjectMapper mapper;

    public HuggingFaceClient(String apiKey) {
        this.apiKey = apiKey;
        this.client = new OkHttpClient();
        this.mapper = new ObjectMapper();
    }

    // 无参构造，自动读取环境变量
    public HuggingFaceClient() {
        this(System.getenv("HF_API_TOKEN"));
    }

    @Override
    public String getName() {
        return "Hugging Face";
    }

    @Override
    public String getReply(List<Message> context) { // MODIFIED: 接收一个列表
        if (apiKey == null || apiKey.isEmpty()) {
            return "请配置 Hugging Face API Token";
        }

        // MODIFIED: 将对话历史拼接成一个字符串
        String concatenatedInput = buildConcatenatedInput(context);

        try {
            // 注意：HuggingFace API对输入长度有限制，这里的简单拼接可能导致超长
            String json = String.format("{\"inputs\":\"%s\",\"parameters\":{\"max_new_tokens\":100}}", concatenatedInput);
            RequestBody body = RequestBody.create(json, MediaType.get("application/json; charset=utf-8"));

            Request request = new Request.Builder()
                    .url(API_URL)
                    .addHeader("Authorization", "Bearer " + apiKey)
                    .post(body)
                    .build();

            try (Response response = client.newCall(request).execute()) {
                if (!response.isSuccessful()) {
                    return "请求失败：" + response.code() + " " + response.body().string();
                }
                String respStr = response.body().string();
                JsonNode node = mapper.readTree(respStr);
                if (node.isArray() && node.size() > 0 && node.get(0).has("generated_text")) {
                    String fullText = node.get(0).get("generated_text").asText();
                    // API会返回包含输入的完整文本，我们需要提取出新生成的部分
                    if (fullText.startsWith(concatenatedInput)) {
                        return fullText.substring(concatenatedInput.length()).trim();
                    }
                    return fullText;
                }
                return "未获取到有效回复";
            }
        } catch (Exception e) {
            return "Hugging Face 请求失败：" + e.getMessage();
        }
    }

    // NEW: 新增一个辅助方法来构建拼接的输入字符串
    private String buildConcatenatedInput(List<Message> context) {
        StringBuilder sb = new StringBuilder();
        for (Message msg : context) {
            // 我们只处理 user 和 assistant 的消息，忽略 system
            if (Role.USER.getValue().equals(msg.getRole())) {
                sb.append("User: ").append(msg.getContent()).append("\n");
            } else if (Role.ASSISTANT.getValue().equals(msg.getRole())) {
                sb.append("AI: ").append(msg.getContent()).append("\n");
            }
        }
        // 添加一个提示，让AI知道轮到它回复了
        sb.append("AI:");
        return sb.toString();
    }
}