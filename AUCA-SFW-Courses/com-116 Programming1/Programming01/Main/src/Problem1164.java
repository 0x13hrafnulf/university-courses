import java.util.*;

public class Problem1164 {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int n = input.nextInt();
		int a = 0;
		int b = 0;
		int sum = 0;
		for (int i=0; i<n; ++i, sum=0, a=0, b=0) {
			int x = input.nextInt();
			while (a<x-1) {
				++a;
				if (x%a==0) {
					sum+=a;
				}
			}
			if (sum==x) {
				System.out.printf("%d eh perfeito\n", x);
			} else {
				System.out.printf("%d nao eh perfeito\n", x);
			}
		}
	}
}
