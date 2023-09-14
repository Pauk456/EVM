#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc == 0) {
		cout << "Error";
	}

	int N = (int)*argv[1];
	ofstream output("rand_arr.txt");
	for (int i = 0; i < N; i++) {
		output << rand() << ' ';
	}
}