package com.velthas;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class FloatingBall {
    private final int ballSize = 80;
    private Point mouseOffset;
    private AIChatWindow chatWindow;
    private Timer timer;
    private JWindow window;

    public void createWindow() {
        window = new JWindow();
        window.setSize(ballSize, ballSize);
        window.setAlwaysOnTop(true);
        window.setBackground(new Color(0,0,0,0));
        window.setLayout(null);

        MemoryBallPanel ballPanel = new MemoryBallPanel();
        ballPanel.setBounds(0,0,ballSize,ballSize);
        window.add(ballPanel);

        // 创建右键菜单
        JPopupMenu popupMenu = new JPopupMenu();

        // NEW: 新对话菜单项
        JMenuItem newConversationItem = new JMenuItem("新对话");
        newConversationItem.addActionListener(e -> {
            if (chatWindow != null) {
                chatWindow.startNewConversation(); // 调用新方法清除对话
                // 确保在点击菜单项后关闭菜单
                popupMenu.setVisible(false);
            }
        });
        popupMenu.add(newConversationItem); // 添加新对话按钮

        // 退出菜单项 (保持在下方)
        JMenuItem exitItem = new JMenuItem("退出");
        exitItem.addActionListener(e -> {
            if (timer != null) {
                timer.stop();
            }
            if (chatWindow != null) {
                chatWindow.dispose();
            }
            window.dispose();
            System.exit(0);
        });
        popupMenu.add(exitItem); // 添加退出按钮

        // 鼠标拖动和点击事件
        MouseAdapter mouseAdapter = new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                mouseOffset = e.getPoint();
                if (SwingUtilities.isRightMouseButton(e)) {
                    popupMenu.show(e.getComponent(), e.getX(), e.getY());
                }
            }
            @Override
            public void mouseDragged(MouseEvent e) {
                if (SwingUtilities.isLeftMouseButton(e)) {
                    Point loc = window.getLocation();
                    window.setLocation(loc.x + e.getX() - mouseOffset.x, loc.y + e.getY() - mouseOffset.y);
                    if (chatWindow != null && chatWindow.isVisible()) {
                        chatWindow.followBall(window.getX(), window.getY(), ballSize);
                    }
                }
            }
            @Override
            public void mouseClicked(MouseEvent e) {
                if (SwingUtilities.isLeftMouseButton(e)) {
                    if (chatWindow == null) chatWindow = new AIChatWindow();
                    chatWindow.setVisible(!chatWindow.isVisible());
                    if (chatWindow.isVisible()) {
                        chatWindow.followBall(window.getX(), window.getY(), ballSize);
                    }
                }
            }
        };
        ballPanel.addMouseListener(mouseAdapter);
        ballPanel.addMouseMotionListener(mouseAdapter);

        // 定时更新内存
        timer = new Timer(500, e -> ballPanel.updateUsage());
        timer.start();

        // 初始位置：右下角
        Rectangle screen = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
        int startX = screen.width - ballSize - screen.width / 50;
        int startY = screen.height - ballSize - screen.height / 3;
        window.setLocation(startX, startY);
        window.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new FloatingBall().createWindow());
    }
}