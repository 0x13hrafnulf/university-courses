import java.util.*;

public class Problem1149 {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int a = input.nextInt();
		int n = input.nextInt();
		int j = 0;
		int i = 0;
		int sum = 0;
		boolean run = true;
		while (run) {
			if (n > 0) {
				i = a;
				while (j<n) {
					sum += i;
					++i;
					++j;
				}
				System.out.println(sum);
				run = false;
			} else {
				n = input.nextInt();
			}
		}
	}
}
