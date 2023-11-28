#pragma once
#include <vector>
#include <iostream>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <limits>

class Matrix
{
private:
	int N;
	float* matrix;
private:
	Matrix calculate_R(Matrix& B);
	Matrix calculate_B();
	float sum_max_row();
	float sum_max_column();
public:
	Matrix(int N);
	~Matrix();
	Matrix(const Matrix& other);
	void reverse_matrix(int M);
	Matrix transpose_matrix() const;
	void to_single();

	// TEST
	float sum_max_row_TEST() { return sum_max_row(); }
	float sum_max_column_TEST() { return sum_max_column(); }
	//

	
	float* operator[](int row)
	{
		return &matrix[row * N];
	}
	const float* operator[](int row) const
	{
		return &matrix[row * N];
	}
	Matrix operator+(const Matrix& b) const;
	Matrix& operator+=(const Matrix& b);
	Matrix operator-(const Matrix& b) const;
	Matrix operator*(const Matrix& b) const;
	Matrix& operator/(const float b);
	Matrix& operator=(const Matrix& other);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);
};

