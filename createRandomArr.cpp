#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Error";
	}

	int N = atoi(argv[1]);
	ofstream output("textarr.txt");
	for (int i = 0; i < N; i++) {
		output << rand() << ' ';
	}
}