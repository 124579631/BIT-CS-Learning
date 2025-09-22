package com.velthas;

import com.alibaba.dashscope.common.Message; // 导入Message类
import java.util.List; // 导入List

public interface AIClient {
    // 修改方法签名，接收一个Message列表作为上下文
    String getReply(List<Message> context);
    String getName();
}