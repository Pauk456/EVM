#include "Mul_Matrix_prim.h"

int main() {
	Matrix A(3);
	A[0][2] = 1;
	A[1][0] = 1;
	A[2][1] = 1;
	A.reverse_matrix(10);
	std::cout << A;
}