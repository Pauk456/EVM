#include "Mul_matrix_prim.h"

Matrix::Matrix(int N)
{
	this->N = N;
	matrix.resize(N, std::vector<float>(N, 0));
}

void Matrix::reverse_matrix(int M)
{
	Matrix B = calculate_B();
	Matrix R = calculate_R(B);
	Matrix Rst = R;
	(*this).to_single();
	for (int i = 0; i < M; i++)
	{
		(*this) += Rst;
		Rst = Rst * R;
	}
	(*this) = (*this) * B;
}

Matrix Matrix::transpose_matrix() const {
	Matrix T(N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			T[j][i] = (*this)[i][j];
		}
	}
	return T;
}

void Matrix::to_single() 
{
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			(*this)[i][j] = i == j ? 1 : 0;
		}
	}
}

Matrix Matrix::operator+(const Matrix& b) const
{
	Matrix Sum(N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			Sum[i][j] = (*this)[i][j] + b[i][j];
		}
	}
	return Sum;
}

Matrix& Matrix::operator+=(const Matrix& b)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			(*this)[i][j] = (*this)[i][j] + b[i][j];
		}
	}
	return (*this);
}

Matrix Matrix::operator-(const Matrix& b) const
{
	Matrix Sub(N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			Sub[i][j] = (*this)[i][j] - b[i][j];
		}
	}
	return Sub;
}

Matrix Matrix::operator*(const Matrix& b) const
{
	Matrix Mul(N); // i - строка, j - столбец
	for (int j1 = 0; j1 < N; j1++) 
	{
		for (int j2 = 0; j2 < N; j2++) 
		{
			for (int i1 = 0; i1 < N; i1++) 
			{
				Mul[i1][j2] += (*this)[i1][j1] * b[j1][j2];
			}
		}
	}
	return Mul;
}

Matrix& Matrix::operator/(const float b) 
{
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
			matrix[i][j] /= b;
		}
	}
	return (*this);
}

Matrix Matrix::calculate_R(Matrix& B)
{
	Matrix I(N);
	I.to_single();
	return I - B * (*this);
}

Matrix Matrix::calculate_B()
{
	float A1 = sum_max_column();
	float A8 = sum_max_row();
	return (*this).transpose_matrix() / (A1 * A8);
}

float Matrix::sum_max_row() // A8
{
	float max_sum = -9999999.0;
	for (int i = 0; i < N; i++) // i - строка, j - столобец
	{
		float Ai = 0; // сумма i ой строчки
		for (int j = 0; j < N; j++)
		{
			Ai += matrix[i][j];
		}
		if (Ai > max_sum)
		{
			max_sum = Ai;
		}
	}
	return max_sum;
}

float Matrix::sum_max_column() // A1
{
	float max_sum = -9999999.0;
	for (int j = 0; j < N; j++) // i - строка, j - столобец
	{
		float Aj = 0; // сумма j ого столбца
		for (int i = 0; i < N; i++)
		{
			Aj += matrix[i][j];
		}
		if (Aj > max_sum)
		{
			max_sum = Aj;
		}
	}
	return max_sum;
}

std::ostream& operator<<(std::ostream& os, const Matrix& obj)
{
	for (int i = 0; i < obj.N; i++)
	{
		for (int j = 0; j < obj.N; j++)
		{
			os << obj[i][j] << ' ';
		}
		os << '\n';
	}
	return os;
}
