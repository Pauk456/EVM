#include "gtest/gtest.h"
#include "Mul_matrix_vectoriz.h"
#include "Mul_Matrix_prim.h"


using namespace std;

using namespace Matrix_vectoriz;
// Max in row

TEST(Matrix_max_row, LargeTest)
{
	int N = 100;
	Matrix D(N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			D[i][j] = 2 * i + j;
		}
	}
	

	// Find the maximum row sum
	float maxRowSum = D.sum_max_row_TEST();

	float expectedMaxRowSum = 0;
	for (int j = 0; j < N; j++)
	{
		expectedMaxRowSum += 2 * (N - 1) + j;
	}

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

// Max in col

TEST(Matrix_max_col, LargeTest1)
{
	// Matrix D with random values
	int N = 1024;
	Matrix D(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			D[i][j] = i + j;
		}
	}
	// Find the maximum row sum
	float maxRowSum = D.sum_max_column_TEST();

	// Expected result (the third row has the maximum sum: 8 + 2 + 7 + 1 = 18)
	float expectedMaxRowSum = 0;
	for (int i = 0; i < N; i++)
	{
		expectedMaxRowSum += (N - 1) + i;
	}

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

TEST(Matrix_max_col, LargeTest2)
{
	// Matrix D with random values
	int N = 1024;
	Matrix D(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			D[i][j] = i + ((N - 1) - j);
		}
	}
	// Find the maximum row sum
	float maxRowSum = D.sum_max_column_TEST();

	// Expected result (the third row has the maximum sum: 8 + 2 + 7 + 1 = 18)
	float expectedMaxRowSum = 0;
	for (int i = 0; i < N; i++)
	{
		expectedMaxRowSum += (N - 1) + i;
	}

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

// Matrix multiplication
TEST(Matrix_mul, LargeTest)
{
	int N = 512; //1024
	Matrix_vectoriz::Matrix VECTORIZ_M1(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				VECTORIZ_M1[i][j] = 1;
			}
			else
			{
				VECTORIZ_M1[i][j] = i + j - 4;
			}
		}
	}
	Matrix_vectoriz::Matrix VECTORIZ_M2(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				VECTORIZ_M2[i][j] = 1;
			}
			else
			{
				VECTORIZ_M2[i][j] = i;
			}
		}
	}
	Matrix_vectoriz::Matrix VECTORIZ_RES = VECTORIZ_M1 * VECTORIZ_M2;

	Matrix_prim::Matrix PRIM_M1(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				PRIM_M1[i][j] = 1;
			}
			else
			{
				PRIM_M1[i][j] = i + j - 4;
			}
		}
	}
	Matrix_prim::Matrix PRIM_M2(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				PRIM_M2[i][j] = 1;
			}
			else
			{
				PRIM_M2[i][j] = i;
			}
		}
	}
	Matrix_prim::Matrix PRIM_RES = PRIM_M1 * PRIM_M2;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			EXPECT_EQ(PRIM_RES[i][j], VECTORIZ_RES[i][j]);
		}
	}
}

TEST(Matrix_mul, LargeTest2)
{
	int N = 512; //1024
	Matrix A(N);
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

	Matrix I(N);
	I.to_single();

	Matrix C = A * I;

	Matrix expected = A;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			EXPECT_EQ(C[i][j], expected[i][j]);
		}
	}
}

// Matrix division on const

TEST(Matrix_division_const, LargeTest)
{
	// Matrix U
	int N = 100;
	Matrix U(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			U[i][j] = i + j + 3;
		}
	}

	Matrix W = U / 5.5123;

	// Expected result
	Matrix expected(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			expected[i][j] = (i + j + 3) / 5.5123;
		}
	}

	// Check each element in the result matrix
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			EXPECT_EQ(W[i][j], expected[i][j]);
		}
	}
}

// Matrix addition

TEST(Matrix_sum, LargeTest)
{
	// Matrix U
	int N = 2048;
	Matrix U(N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
			U[i][j] = i + j + 3;
		}
	}

	// Matrix V
	Matrix V(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			V[i][j] = i - j + 4;
		}
	}

	// Matrix W = U + V
	Matrix W = U + V;

	// Expected result
	Matrix expected(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			expected[i][j] = 2 * i + 7;
		}
	}

	// Check each element in the result matrix
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			EXPECT_EQ(W[i][j], expected[i][j]);
		}
	}
}

// Matrix subtraction

TEST(Matrix_sub, LargeTest)
{
	// Matrix U
	int N = 128;
	Matrix U(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			U[i][j] = i + j + 3;
		}
	}

	// Matrix V
	Matrix V(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			V[i][j] = i - j + 4;
		}
	}

	// Matrix W = U + V
	Matrix W = U - V;

	// Expected result
	Matrix expected(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			expected[i][j] = 2 * j - 1;
		}
	}

	// Check each element in the result matrix
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			EXPECT_EQ(W[i][j], expected[i][j]);
		}
	}
}

// Matrix transpose

TEST(Matrix_trsp, LargeTest)
{
	// Matrix P
	int N = 1024; //1024
	Matrix A(N);
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
				A[i][j] = j * 4 + 1;
			}
		}
	}

	Matrix Q = A.transpose_matrix();

	Matrix expected(N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				expected[i][j] = 1;
			}
			else
			{
				expected[j][i] = j * 4 + 1;
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			EXPECT_EQ(Q[i][j], expected[i][j]);
		}
	}
}

// Matrix reverse

TEST(Matrix_rev, vectorizTest)
{
	int N = 16;
	Matrix A(N);
	for (int i = 0; i < N; ++i) 
	{
		for (int j = 0; j < N; ++j) 
		{
			if(i == j) 
			{
				A[i][j] = 1;
			}
			else
			{
				A[i][j] = i + j + 1;
			}
		}
	}

	Matrix AReverse = A;
	AReverse.reverse_matrix(10000);
	
	Matrix I = A * AReverse;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == j) {
				float tset = I[i][j];
				EXPECT_NEAR(I[i][j], 1.0, 1);
			}
			else {
				float tset = I[i][j];
				EXPECT_NEAR(I[i][j], 0.0, 1);
			}
		}
	}
}
