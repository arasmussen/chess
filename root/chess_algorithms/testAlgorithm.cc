#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char **argv) {
	char buf[20];

	cin >> buf;

	if (strcmp(buf, "Black") == 0) {
		cin >> buf;
	}

	cout << "FistMove";

	cin >> buf;
	cout << "SecondMove"; 
	
	string tok;
	cin >> tok;
}
