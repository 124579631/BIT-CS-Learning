package com.velthas;

import com.alibaba.dashscope.aigc.generation.Generation;
import com.alibaba.dashscope.aigc.generation.GenerationParam;
import com.alibaba.dashscope.aigc.generation.GenerationResult;
import com.alibaba.dashscope.common.Message;
import com.alibaba.dashscope.exception.ApiException;
import com.alibaba.dashscope.exception.InputRequiredException;
import com.alibaba.dashscope.exception.NoApiKeyException;

import java.util.List; // 导入List

public class AliyunClient implements AIClient {

    private final String apiKey;
    private final Generation generation;

    public AliyunClient(String apiKey) {
        this.apiKey = apiKey;
        this.generation = new Generation();
    }

    @Override
    public String getReply(List<Message> context) { // MODIFIED: 接收一个列表
        if (apiKey == null || apiKey.isEmpty()) {
            return "请配置阿里云 API Key";
        }

        GenerationParam param = GenerationParam.builder()
                .apiKey(apiKey)
                .model("qwen-plus")
                .messages(context) // MODIFIED: 直接使用传入的上下文
                .resultFormat(GenerationParam.ResultFormat.MESSAGE)
                .build();

        try {
            GenerationResult result = generation.call(param);
            return result.getOutput().getChoices().get(0).getMessage().getContent();
        } catch (ApiException | NoApiKeyException | InputRequiredException e) {
            return "阿里云请求失败: " + e.getMessage();
        }
    }

    @Override
    public String getName() {
        return "阿里云";
    }
}