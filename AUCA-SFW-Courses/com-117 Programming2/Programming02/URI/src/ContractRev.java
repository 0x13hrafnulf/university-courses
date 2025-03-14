import java.util.*;

public class ContractRev {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while (true) {
			String m1 = input.next();
			String m2 = input.next();
			if (m1.equals("0") && m2.equals("0")) {
				break;
			}
			rev(m1, m2);
		}
	}

	static void rev(String m1, String m2) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < m2.length(); ++i) {
			char c1 = m1.charAt(0);
			char c2 = m2.charAt(i);
			if (c2 != c1) {
				sb.append(c2);
			}
			if (c2 == c1) {
				sb.append("");
			}
		}
		int count = 0;
		for (int i = 0; i < sb.length(); ++i) {
			char c = sb.charAt(i);
			if (c == '0') {
				count++;
			}
			if (count == sb.length()) {
				sb = new StringBuilder("0");
			}
		}
		System.out.println(sb);
	}
}
