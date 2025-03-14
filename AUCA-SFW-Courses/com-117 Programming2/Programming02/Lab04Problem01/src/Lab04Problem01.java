import java.util.*;

public class Lab04Problem01 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);

		ArrayList<Integer> list = new ArrayList<Integer>();

		while (scan.hasNextInt()) {
			int x = scan.nextInt();
			list.add(x);
		}

		System.out.print("Before reversing: ");
		for (int i = 0; i < list.size(); i++) {
			System.out.print(list.get(i) + " ");
		}
		System.out.println();
		
		int p1 = 0;
		int p2 = list.size() - 1;
		while (p1<p2) {
			int t = list.get(p1);
			list.set(p1, list.get(p2));
			list.set(p2, t);
			++p1;
			--p2;
		}
		
		System.out.print("After reversing: ");
		for (int i = 0; i < list.size(); i++) {
			System.out.print(list.get(i) + " ");
		}
		System.out.println();
	}
}
