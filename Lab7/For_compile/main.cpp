#include "Mul_Matrix_prim.h"
#include "Mul_Matrix_vectoriz.h"
#include "Matrix_BLAS.h"
#include "Mul_Matrix_vectoriz.cpp"
#include "Mul_Matrix_prim.cpp"
#include <time.h>

double time_prim(int N)
{
	double time_spent = 0.0;
	clock_t begin = clock();

	Matrix_prim::Matrix A(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				A[i][j] = 1;
			}
			else
			{
				A[i][j] = i + j + 1;
			}
		}
	}

	Matrix_prim::Matrix AReverse = A;
	AReverse.reverse_matrix(10000);

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	return time_spent;
}

double time_vectoriz(int N)
{
	double time_spent = 0.0;
	clock_t begin = clock();

	Matrix_vectoriz::Matrix A(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				A[i][j] = 1;
			}
			else
			{
				A[i][j] = i + j + 1;
			}
		}
	}

	Matrix_vectoriz::Matrix AReverse = A;
	AReverse.reverse_matrix(10000);

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	return time_spent;
}

double time_blas(int N)
{
	double time_spent = 0.0;
	clock_t begin = clock();

	Matrix_blas::Matrix A(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				A[i][j] = 1;
			}
			else
			{
				A[i][j] = i + j + 1;
			}
		}
	}

	Matrix_blas::Matrix AReverse = A;
	AReverse.reverse_matrix(10000);

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	return time_spent;
}

int main() {
	int N = 16;
	std::cout << time_prim(N) << '\n';
	std::cout << time_vectoriz(N) << '\n';
	std::cout << time_blas(N) << '\n';
}