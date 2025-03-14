import java.util.*;

public class Puzzle {
	Random rnd = new Random();
	int[][] puzzle = new int[4][4];
	int empX = 0;
	int empY = 0;

	public Puzzle() {
		start();
	}
	
	public void start() {
		int a = 1;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				puzzle[i][j] = a;
				++a;
			}
		}
		coorEmp();
	}
	
	public int getEmpX() {
		return empX;
	}
	
	public int getEmpY() {
		return empY;
	}
	
	public void coorEmp() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (puzzle[i][j] == 16) {
					empX = j;
					empY = i;
				}
			}
		}
	}

	public void print() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (puzzle[i][j] == 16)
					System.out.print("   ");
				else
					System.out.printf("%3d", puzzle[i][j]);
			}
			System.out.println();
		}
		coorEmp();
	}

	public void shuffle(int shfl) {
		for (int i = 0; i < shfl; i++) {
			coorEmp();
			int random = rnd.nextInt(4);
			int temp = puzzle[empY][empX];
			switch (random) {
			case 0:
				if (empY > 0) {
					puzzle[empY][empX] = puzzle[empY - 1][empX];
					puzzle[empY - 1][empX] = temp;
				}
				break;
			case 2:
				if (empY < 3) {
					puzzle[empY][empX] = puzzle[empY + 1][empX];
					puzzle[empY + 1][empX] = temp;
				}
				break;
			case 3:
				if (empX > 0) {
					puzzle[empY][empX] = puzzle[empY][empX - 1];
					puzzle[empY][empX - 1] = temp;
				}
				break;
			case 1:
				if (empX < 3) {
					puzzle[empY][empX] = puzzle[empY][empX + 1];
					puzzle[empY][empX + 1] = temp;
				}
				break;
			}
		}
		coorEmp();
	}

	public void move(String move) {
		int temp = puzzle[empY][empX];
		switch (move) {
		case "S":
			if (empY > 0) {
				puzzle[empY][empX] = puzzle[empY - 1][empX];
				puzzle[empY - 1][empX] = temp;
			}
			break;
		case "W":
			if (empY < 3) {
				puzzle[empY][empX] = puzzle[empY + 1][empX];
				puzzle[empY + 1][empX] = temp;
			}
			break;
		case "D":
			if (empX > 0) {
				puzzle[empY][empX] = puzzle[empY][empX - 1];
				puzzle[empY][empX - 1] = temp;
			}
			break;
		case "A":
			if (empX < 3) {
				puzzle[empY][empX] = puzzle[empY][empX + 1];
				puzzle[empY][empX + 1] = temp;
			}
			break;
		}
	}

	public int solved() {
		int a = 1;
		int count = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (puzzle[i][j] == a) count++;
				++a;
			}
		}
		return count;
	}
}
