import java.util.*;

public class Console {
	static Puzzle puzzle = new Puzzle();
	static Scanner input = new Scanner(System.in);
	
	public static void main(String[] args) {
		start();
		
		play();
		
		result();
	}

	private static void start() {
		System.out.println("15 puzzle:");
		puzzle.print();

		System.out.print("Number of moves for shuffle? ");
		int shfl = input.nextInt();
		puzzle.shuffle(shfl);
		puzzle.print();		
	}

	private static void play() {
		while (puzzle.solved() != 16) {
			System.out.println();
			System.out.print("Your move (W, D, S, A): ");
			String move = input.next();
			puzzle.move(move);
			puzzle.print();
		}		
	}
	
	private static void result() {
		while (puzzle.solved() == 16) {
			System.out.println("You are winner!");
			System.out.print("New game? (Y/N): ");
			String decision = input.next();
			if (decision.equals("Y")) {
				start();
				play();
			} else if (decision.equals("N")) {
				System.out.println("Have a good time.");
				break;
			}
		}		
	}
}
