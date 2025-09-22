package com.velthas;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D; // 导入 Ellipse2D
import java.lang.management.ManagementFactory;
import com.sun.management.OperatingSystemMXBean;

public class MemoryBallPanel extends JPanel {
    private float usage = 0.1f;

    public MemoryBallPanel() {
        setOpaque(false);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g.create();
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        int w = getWidth();
        int h = getHeight();

        // 创建一个圆形裁剪区域。后续所有绘制都将限制在这个圆形内部。
        // Ellipse2D.Double(x, y, width, height)
        Ellipse2D circle = new Ellipse2D.Double(0, 0, w, h);
        g2.setClip(circle); // 将图形上下文的裁剪区域设置为这个圆形

        // 1. 绘制白色球形背景（在裁剪区域内）
        g2.setColor(Color.WHITE);
        g2.fill(circle); // 使用fill(Shape)来填充圆形

        // 2. 水面颜色
        // 根据usage调整颜色，从蓝色到绿色
        // blue = usage * 255; green = (1-usage) * 255;
        // 这样usage低时偏绿，高时偏蓝，模拟水体颜色变化
        int currentGreen = Math.max(0, 255 - (int)(usage * 255));
        int currentBlue = Math.min(255, (int)(usage * 255)); // 确保不超出255
        Color waterColor = new Color(0, currentGreen, currentBlue);
        g2.setColor(waterColor);

        // 3. 水面高度
        // waterHeight是从底部开始计算的填充高度
        int waterHeight = (int)(usage * h);
        // 确保最低水面可见，避免usage接近0时完全看不到水
        waterHeight = Math.max(5, waterHeight); // 最低5像素，可调整

        // 绘制水面矩形。由于已经设置了圆形裁剪，这个矩形只会显示在圆形内部。
        // 矩形从球体底部向上填充
        g2.fillRect(0, h - waterHeight, w, waterHeight);

        // 绘制完成后，取消裁剪区域，以防影响后续绘制（虽然在这个方法里没有后续绘制）
        g2.setClip(null);

        // 4. 球边框 (应该在裁剪之后绘制，否则会被裁剪掉)
        // 边框应该绘制在整个组件的边界，而不是被裁剪
        g2.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(2));
        g2.drawOval(0, 0, w-1, h-1); // 绘制圆形边框，注意w-1和h-1防止部分边框被切掉

        // 5. 中心显示百分比
        g2.setColor(Color.BLACK);
        g2.setFont(new Font("Arial", Font.BOLD, 14));
        String text = String.format("%d%%", (int)(usage * 100));
        FontMetrics fm = g2.getFontMetrics();
        int tx = (w - fm.stringWidth(text)) / 2;
        int ty = (h + fm.getAscent()) / 2 - 2;
        g2.drawString(text, tx, ty);

        g2.dispose();
    }

    // 更新物理内存占用
    public void updateUsage() {
        OperatingSystemMXBean osBean =
                (OperatingSystemMXBean) ManagementFactory.getOperatingSystemMXBean();
        long total = osBean.getTotalPhysicalMemorySize();
        long free = osBean.getFreePhysicalMemorySize();
        long used = total - free;
        // 确保使用率在0到1之间，并且设定一个最低值，避免浮球完全空置
        usage = Math.max(0.05f, Math.min(1.0f, (float) used / total));
        repaint();
    }
}