#include "gtest/gtest.h"
#include "Mul_matrix_vectoriz.h"

using namespace std;

// Max in row
TEST(Matrix_max_row, ExampleTest)
{
	// Matrix A
	Matrix A(2);
	A[0][0] = 1; A[0][1] = 0;
	A[1][0] = 1; A[1][1] = 1;

	// Find the maximum row sum
	float maxRowSum = A.sum_max_row_TEST();

	// Expected result
	float expectedMaxRowSum = 2;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

TEST(Matrix_max_row, ZeroMatrixTest)
{
	// Matrix B (zero matrix)
	Matrix C(2);

	// Find the maximum row sum
	float maxRowSum = C.sum_max_row_TEST();

	// Expected result (since all elements are zero, the maximum row sum should be zero)
	float expectedMaxRowSum = 0;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

TEST(Matrix_max_row, NegativeValuesTest)
{
	// Matrix C with negative values
	Matrix C(3);
	C[0][0] = -2; C[0][1] = -5; C[0][2] = -3;
	C[1][0] = 1; C[1][1] = -1; C[1][2] = -2;
	C[2][0] = 4; C[2][1] = 2; C[2][2] = -6;

	// Find the maximum row sum
	float maxRowSum = C.sum_max_row_TEST();

	// Expected result (the second row has the maximum sum: 1 - 1 - 2 = -2)
	float expectedMaxRowSum = 0;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

TEST(Matrix_max_row, RandomValuesTest)
{
	// Matrix D with random values
	Matrix D(4);
	D[0][0] = 3; D[0][1] = 7; D[0][2] = 1; D[0][3] = 2;
	D[1][0] = 5; D[1][1] = 4; D[1][2] = 6; D[1][3] = 9;
	D[2][0] = 8; D[2][1] = 2; D[2][2] = 7; D[2][3] = 1;
	D[3][0] = 0; D[3][1] = 3; D[3][2] = 5; D[3][3] = 4;

	// Find the maximum row sum
	float maxRowSum = D.sum_max_row_TEST();

	// Expected result (the third row has the maximum sum: 8 + 2 + 7 + 1 = 18)
	float expectedMaxRowSum = 24;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

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

TEST(Matrix_max_col, ExampleTest)
{
	// Matrix A
	Matrix A(2);
	A[0][0] = 1; A[0][1] = 0;
	A[1][0] = 1; A[1][1] = 1;

	// Find the maximum row sum
	float maxRowSum = A.sum_max_column_TEST();

	// Expected result
	float expectedMaxRowSum = 2;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

TEST(Matrix_max_col, ZeroMatrixTest)
{
	// Matrix B (zero matrix)
	Matrix C(2);

	// Find the maximum row sum
	float maxRowSum = C.sum_max_column_TEST();

	// Expected result (since all elements are zero, the maximum row sum should be zero)
	float expectedMaxRowSum = 0;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

TEST(Matrix_max_col, NegativeValuesTest)
{
	// Matrix C with negative values
	Matrix C(3);
	C[0][0] = -2; C[0][1] = -5; C[0][2] = -3;
	C[1][0] = -1; C[1][1] = -1; C[1][2] = -2;
	C[2][0] = -1; C[2][1] = 0; C[2][2] = -6;

	// Find the maximum row sum
	float maxRowSum = C.sum_max_column_TEST();

	// Expected result (the second row has the maximum sum: 1 - 1 - 2 = -2)
	float expectedMaxRowSum = -4;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

TEST(Matrix_max_col, RandomValuesTest)
{
	// Matrix D with random values
	Matrix D(4);
	D[0][0] = 3; D[0][1] = 7; D[0][2] = 1; D[0][3] = 2;
	D[1][0] = 5; D[1][1] = 4; D[1][2] = 6; D[1][3] = 9;
	D[2][0] = 8; D[2][1] = 2; D[2][2] = 7; D[2][3] = 1;
	D[3][0] = 0; D[3][1] = 3; D[3][2] = 5; D[3][3] = 4;

	// Find the maximum row sum
	float maxRowSum = D.sum_max_column_TEST();

	// Expected result (the third row has the maximum sum: 8 + 2 + 7 + 1 = 18)
	float expectedMaxRowSum = 19;

	// Check if the result matches the expected value
	EXPECT_EQ(maxRowSum, expectedMaxRowSum);
}

// Matrix multiplication

//TEST(Matrix_mul, test1)
//{
//	Matrix A(3);
//	A[0][0] = 1; A[0][1] = 0; A[0][2] = 0;
//	A[1][0] = 1; A[1][1] = 0; A[1][2] = 1;
//	A[2][0] = 1; A[2][1] = 1; A[2][2] = 1;
//
//	Matrix B(3);
//	B[0][0] = 1; B[0][1] = 0; B[0][2] = 0;
//	B[1][0] = 0; B[1][1] = 1; B[1][2] = 0;
//	B[2][0] = 0; B[2][1] = 0; B[2][2] = 1;
//
//	Matrix C = A * B;
//
//	// Expected result
//	Matrix expected(3);
//	expected[0][0] = 1; expected[0][1] = 0; expected[0][2] = 0;
//	expected[1][0] = 1; expected[1][1] = 0; expected[1][2] = 1;
//	expected[2][0] = 1; expected[2][1] = 1; expected[2][2] = 1;
//
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 3; ++j) {
//			EXPECT_EQ(C[i][j], expected[i][j]);
//		}
//	}
//}
//
//TEST(Matrix_mul, test2)
//{
//	Matrix A(3);
//	A[0][0] = 1; A[0][1] = 0; A[0][2] = 0;
//	A[1][0] = 1; A[1][1] = 0; A[1][2] = 1;
//	A[2][0] = 1; A[2][1] = 1; A[2][2] = 1;
//
//	Matrix B(3);
//	B[0][0] = 1; B[0][1] = 0; B[0][2] = 1;
//	B[1][0] = 0; B[1][1] = 1; B[1][2] = 0;
//	B[2][0] = 1; B[2][1] = 0; B[2][2] = 1;
//
//	Matrix C = A * B;
//
//	// Expected result
//	Matrix expected(3);
//	expected[0][0] = 1; expected[0][1] = 0; expected[0][2] = 1;
//	expected[1][0] = 2; expected[1][1] = 0; expected[1][2] = 2;
//	expected[2][0] = 2; expected[2][1] = 1; expected[2][2] = 2;
//
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 3; ++j) {
//			EXPECT_EQ(C[i][j], expected[i][j]);
//		}
//	}
//}
//
//TEST(Matrix_mul, test3)
//{
//	Matrix A(3);
//	A[0][0] = 2; A[0][1] = 1; A[0][2] = 0;
//	A[1][0] = 0; A[1][1] = 1; A[1][2] = 1;
//	A[2][0] = 1; A[2][1] = 0; A[2][2] = 1;
//
//	Matrix B(3);
//	B[0][0] = 1; B[0][1] = 2; B[0][2] = 0;
//	B[1][0] = 0; B[1][1] = 1; B[1][2] = 1;
//	B[2][0] = 1; B[2][1] = 1; B[2][2] = 1;
//
//	Matrix C = A * B;
//
//	// Expected result
//	Matrix expected(3);
//	expected[0][0] = 2; expected[0][1] = 5; expected[0][2] = 1;
//	expected[1][0] = 1; expected[1][1] = 2; expected[1][2] = 2;
//	expected[2][0] = 2; expected[2][1] = 3; expected[2][2] = 1;
//
//	// Check each element in the result matrix
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 3; ++j) {
//			EXPECT_EQ(C[i][j], expected[i][j]);
//		}
//	}
//}
//
//TEST(Matrix_mul, test4)
//{
//	Matrix A(2);
//	A[0][0] = 2; A[0][1] = 1;
//	A[1][0] = 3; A[1][1] = 0;
//
//	Matrix B(2);
//	B[0][0] = 1; B[0][1] = 2;
//	B[1][0] = 0; B[1][1] = 1;
//
//	Matrix C = A * B;
//
//	Matrix expected(2);
//	expected[0][0] = 2; expected[0][1] = 5;
//	expected[1][0] = 3; expected[1][1] = 6;
//
//	for (int i = 0; i < 2; ++i) {
//		for (int j = 0; j < 2; ++j) {
//			EXPECT_EQ(C[i][j], expected[i][j]);
//		}
//	}
//}

TEST(Matrix_mul, LargeTest)
{
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

TEST(Matrix_sum, test1)
{
	Matrix P(3);
	P[0][0] = 1; P[0][1] = 2; P[0][2] = 3;
	P[1][0] = 4; P[1][1] = 5; P[1][2] = 6;
	P[2][0] = 7; P[2][1] = 8; P[2][2] = 9;

	// Matrix Q
	Matrix Q(3);
	Q[0][0] = 9; Q[0][1] = 8; Q[0][2] = 7;
	Q[1][0] = 6; Q[1][1] = 5; Q[1][2] = 4;
	Q[2][0] = 3; Q[2][1] = 2; Q[2][2] = 1;

	// Matrix R = P + Q
	Matrix R = P + Q;

	// Expected result
	Matrix expected(3);
	expected[0][0] = 10; expected[0][1] = 10; expected[0][2] = 10;
	expected[1][0] = 10; expected[1][1] = 10; expected[1][2] = 10;
	expected[2][0] = 10; expected[2][1] = 10; expected[2][2] = 10;

	// Check each element in the result matrix
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			EXPECT_EQ(R[i][j], expected[i][j]);
		}
	}
}

TEST(Matrix_sum, test2)
{
	// Matrix U
	Matrix U(2);
	U[0][0] = 1; U[0][1] = 2;
	U[1][0] = 3; U[1][1] = 4;

	// Matrix V
	Matrix V(2);
	V[0][0] = 5; V[0][1] = 6;
	V[1][0] = 7; V[1][1] = 8;

	// Matrix W = U + V
	Matrix W = U + V;

	// Expected result
	Matrix expected(2);
	expected[0][0] = 6; expected[0][1] = 8;
	expected[1][0] = 10; expected[1][1] = 12;

	// Check each element in the result matrix
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			EXPECT_EQ(W[i][j], expected[i][j]);
		}
	}
}

TEST(Matrix_sum, LargeTest)
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

TEST(Matrix_sub, test1)
{
	// Matrix P
	Matrix P(3);
	P[0][0] = 1; P[0][1] = 2; P[0][2] = 3;
	P[1][0] = 4; P[1][1] = 5; P[1][2] = 6;
	P[2][0] = 7; P[2][1] = 8; P[2][2] = 9;

	// Matrix Q
	Matrix Q(3);
	Q[0][0] = 9; Q[0][1] = 8; Q[0][2] = 7;
	Q[1][0] = 6; Q[1][1] = 5; Q[1][2] = 4;
	Q[2][0] = 3; Q[2][1] = 2; Q[2][2] = 1;

	// Matrix R = P - Q
	Matrix R = P - Q;

	// Expected result
	Matrix expected(3);
	expected[0][0] = -8; expected[0][1] = -6; expected[0][2] = -4;
	expected[1][0] = -2; expected[1][1] = 0; expected[1][2] = 2;
	expected[2][0] = 4; expected[2][1] = 6; expected[2][2] = 8;

	// Check each element in the result matrix
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			EXPECT_EQ(R[i][j], expected[i][j]);
		}
	}
}

TEST(Matrix_sub, test2)
{
	// Matrix X
	Matrix X(2);
	X[0][0] = 5; X[0][1] = 3;
	X[1][0] = 1; X[1][1] = 8;

	// Matrix Y
	Matrix Y(2);
	Y[0][0] = 2; Y[0][1] = 1;
	Y[1][0] = 4; Y[1][1] = 6;

	// Matrix Z = X - Y
	Matrix Z = X - Y;

	// Expected result
	Matrix expected(2);
	expected[0][0] = 3; expected[0][1] = 2;
	expected[1][0] = -3; expected[1][1] = 2;

	// Check each element in the result matrix
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			EXPECT_EQ(Z[i][j], expected[i][j]);
		}
	}
}

TEST(Matrix_sub, LargeTest)
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

TEST(Matrix_trsp, test1)
{
	// Matrix P
	Matrix P(3);
	P[0][0] = 1; P[0][1] = 2; P[0][2] = 3;
	P[1][0] = 4; P[1][1] = 5; P[1][2] = 6;
	P[2][0] = 7; P[2][1] = 8; P[2][2] = 9;

	// Matrix Q = transpose of P
	Matrix Q = P.transpose_matrix();

	// Expected result
	Matrix expected(3);
	expected[0][0] = 1; expected[0][1] = 4; expected[0][2] = 7;
	expected[1][0] = 2; expected[1][1] = 5; expected[1][2] = 8;
	expected[2][0] = 3; expected[2][1] = 6; expected[2][2] = 9;

	// Check each element in the result matrix
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			EXPECT_EQ(Q[i][j], expected[i][j]);
		}
	}
}

TEST(Matrix_trsp, test2)
{
	// Matrix U
	Matrix U(2);
	U[0][0] = 1; U[0][1] = 2;
	U[1][0] = 3; U[1][1] = 4;

	// Matrix V = transpose of U
	Matrix V = U.transpose_matrix();

	// Expected result
	Matrix expected(2);
	expected[0][0] = 1; expected[0][1] = 3;
	expected[1][0] = 2; expected[1][1] = 4;

	// Check each element in the result matrix
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			EXPECT_EQ(V[i][j], expected[i][j]);
		}
	}
}

// Matrix reverse

//TEST(Matrix_rev, test1)
//{
//	Matrix A(3);
//	A[0][2] = 1;
//	A[1][0] = 1;
//	A[2][1] = 1;
//
//	A.reverse_matrix(10);
//
//	EXPECT_EQ(A[0][0], 0);
//	EXPECT_EQ(A[0][1], 1);
//	EXPECT_EQ(A[0][2], 0);
//
//	EXPECT_EQ(A[1][0], 0);
//	EXPECT_EQ(A[1][1], 0);
//	EXPECT_EQ(A[1][2], 1);
//
//	EXPECT_EQ(A[2][0], 1);
//	EXPECT_EQ(A[2][1], 0);
//	EXPECT_EQ(A[2][2], 0);
//}
//
//TEST(Matrix_rev, test2)
//{
//	// Matrix A
//	Matrix A(2);
//	A[0][0] = 1; A[0][1] = 2;
//	A[1][0] = 3; A[1][1] = 4;
//
//	// Find the inverse of A
//	A.reverse_matrix(1000);
//
//	// Check if the product is approximately the identity matrix
//	EXPECT_NEAR(A[0][0], -2, 1e-1);		EXPECT_NEAR(A[0][1], 1, 1e-1);
//	EXPECT_NEAR(A[1][0], 1.5, 1e-1);	EXPECT_NEAR(A[1][1], -0.5, 1e-1);
//}
//
//TEST(Matrix_rev, test3)
//{
//	// Matrix A
//	Matrix A(2);
//	A[0][0] = 4; A[0][1] = 7;
//	A[1][0] = 2; A[1][1] = 6;
//
//	// Find the inverse of A
//	A.reverse_matrix(200);
//
//	// Check if the product is approximately the identity matrix
//	EXPECT_NEAR(A[0][0], 0.6, 0.5);	EXPECT_NEAR(A[0][1], -0.7, 0.5);
//	EXPECT_NEAR(A[1][0], -0.2, 0.5);	EXPECT_NEAR(A[1][1], 0.4, 0.5);
//}
//
//TEST(Matrix_rev, test4)
//{
//	Matrix A(3);
//	A[0][0] = 1; A[0][1] = 0; A[0][2] = 0;
//	A[1][0] = 1; A[1][1] = 0; A[1][2] = 1;
//	A[2][0] = 1; A[2][1] = 1; A[2][2] = 1;
//
//	A.reverse_matrix(100);
//
//	EXPECT_NEAR(A[0][0], 1, 0.5);	EXPECT_NEAR(A[0][1], 0, 0.5);	EXPECT_NEAR(A[0][2], 0, 0.5);
//	EXPECT_NEAR(A[1][0], 0, 0.5);	EXPECT_NEAR(A[1][1], -1, 0.5);	EXPECT_NEAR(A[1][2], 1, 0.5);
//	EXPECT_NEAR(A[2][0], -1, 0.5);	EXPECT_NEAR(A[2][1], 1, 0.5);	EXPECT_NEAR(A[2][2], 0, 0.5);
//}

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
