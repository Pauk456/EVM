#pragma once
#include "Mul_Matrix_prim.h"
#include <vector>
#include <iostream>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <emmintrin.h>
#include <limits>

namespace Matrix_vectoriz
{
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

		void copy(Matrix_prim::Matrix& copy)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					(*this)[i][j] = copy[i][j];
				}
			}
		}

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
}
