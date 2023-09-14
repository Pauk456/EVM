#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	/*ifstream input("input.txt");
	vector<int> arr;
	int numb;

	while (input >> numb) {
		arr.push_back(numb);
	}

	for (int i = 0; i < arr.size() - 1; i++) {
		for (int j = 0; j < arr.size() - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = arr[j];
			}
		}
	}

	input.close();

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);*/
	int c = 0;
	for (int i = 0; i < 1000000; i++) {
		c++;
	}
	printf("Time taken: %lf sec.\n",
		end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
}