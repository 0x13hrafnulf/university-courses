import java.util.*;

public class Problem1156 {

	public static void main(String[] args) {
		Locale.setDefault(Locale.US); 
		double a = 1;
		double b = 1;
		double c = a;
		double s = 0;
		while (a<39) {
			c = a/b;
			a+=2;
			b*=2;
			s+=c;
		}
		System.out.printf("%.2f\n", s);
	}
}
