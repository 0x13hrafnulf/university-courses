#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

int main() {
	
	cout << "number of month: ";
	int m; cin >> m;

	switch (m) {
		case 12: case 1: case 2:
			cout << "Winter" << endl;
			break;
		
		case 3: case 4: case 5:
			cout << "Spring" << endl;
			break;
		
		case 6: case 7: case 8:
			cout << "Summer" << endl;
			break;
		
		case 9: case 10: case 11:
			cout << "Fall" << endl;
			break;
		
		default:
			cout << "Incorrect number of month" << endl;
			break;
	}
	
	return 0;
}






