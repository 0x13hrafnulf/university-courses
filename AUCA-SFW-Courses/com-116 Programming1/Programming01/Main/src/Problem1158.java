import java.util.*;

public class Problem1158 {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int n = input.nextInt();
		int a = 0;
		int b = 0;
		int sum = 0;
		for (int i=0; i<n; ++i, sum=0, a=0, b=0) {
			int x = input.nextInt();
			int y = input.nextInt();
			a+=x;
			while (b<y) {
				if (a%2!=0) {
					sum+=a;
					++b;
				}
				++a;
			}
			System.out.println(sum);
		}
	}
}
