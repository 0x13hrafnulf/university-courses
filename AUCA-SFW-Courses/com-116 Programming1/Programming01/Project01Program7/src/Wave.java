import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class Wave extends JFrame {
	String title = "Wave";
	Color background = Color.BLACK;
	
	int h = getHeight();
	int w = getWidth();
	int x = 0;
	int y = 0;
	
	void draw(Graphics g) {
		g.setColor(Color.RED);
		for (int i = 0; i < 6; ++i) {
			drawSin(g, x, y);
			x += 360;
		}
	}

	void drawSin(Graphics g, int x, int y) {
		
		for (int i = 0; i < 360; ++i) {
			x = x+1;
			y = (int) (h / 2 - Math.sin(Math.toRadians(i)) * 180);
			g.drawLine(x, y, x, y);	
		}
	}

	public Wave() {
		setTitle(title);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		DrawPanel panel = new DrawPanel();

		panel.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				System.exit(0);
			}
		});

		add(panel);

		setUndecorated(true);
		setExtendedState(JFrame.MAXIMIZED_BOTH);
		setVisible(true);
	}

	public static void main(String[] args) {
		new Wave();
	}

	class DrawPanel extends JPanel {
		public DrawPanel() {
			setBackground(background);
			setFocusable(true);
			requestFocusInWindow();
			setDoubleBuffered(true);
		}

		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			draw(g);
		}
	}
}
