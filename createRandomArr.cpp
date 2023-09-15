#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc == 0) {
		cout << "Error";
	}

	int N = atoi(argv[1]);
	ofstream output("TextArr.txt");
	for (int i = 0; i < N; i++) {
		output << rand() << ' ';
	}
}