#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char **argv) {
	char player[20];
	char buf[20];

	cin >> player;

	if (strcmp(player, "Black") == 0) {
		cin >> buf;
		cerr << "Black Recieve: " << buf << endl;
	
		cout << "BlackFirstMove";

		cin >> buf;
		cerr << "Black Recieve: " << buf << endl;
	} else {
		cout << "WhiteFirstMove";

		cin >> buf;
		cerr << "White Recieve: " << buf << endl;

		cout << "WhiteSecondMove";

		cin >> buf;
		cerr << "White Recieve: " << buf << endl;
	}
}
