#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

int main() {
	struct timespec start, end;

	ifstream input("textarr.txt");
	int* arr = new int[60000];
	int numb;

	int size = 0;
	while (input >> numb) {
		arr[size] = numb;
		size++;
	}

	input.close();

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	printf("%lf\n",
		end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
	ofstream out("out.txt");
	for (int i = 0; i < size; i++) {
		out << arr[i];
	}
}