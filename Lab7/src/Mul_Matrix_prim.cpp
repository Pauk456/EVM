#include "Mul_matrix_prim.h"

namespace Matrix_prim
{
	Matrix::Matrix(int N)
	{
		this->N = N;
		matrix = new float[N * N];
		for(int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				(*this)[i][j] = 0;
			}
		}
	}

	Matrix::~Matrix()
	{
		delete[] matrix;
	}

	Matrix::Matrix(const Matrix& other)
	{
		N = other.N;
		matrix = new float[N * N];
		for (int i = 0; i < N * N; ++i)
		{
			matrix[i] = other.matrix[i];
		}
	}

	Matrix::Matrix(Matrix&& other)
	{
		matrix = other.matrix;
		N = other.N;
		other.matrix = nullptr;
		other.N = 0;
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
		for (int row1 = 0; row1 < N; row1++)
		{
			for (int col2 = 0; col2 < N; col2++)
			{
				for (int col1 = 0; col1 < N; col1++)
				{
					Mul[row1][col2] += (*this)[row1][col1] * b[col1][col2];
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
				(*this)[i][j] /= b;
			}
		}
		return (*this);
	}

	Matrix& Matrix::operator=(const Matrix& other) {
		if (this == &other) {
			return *this;
		}

		delete[] matrix;

		N = other.N;
		matrix = new float[N * N];

		for (int i = 0; i < N * N; ++i) {
			matrix[i] = other.matrix[i];
		}

		return *this;
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
		float max_sum = std::numeric_limits<float>::lowest();
		for (int i = 0; i < N; i++) // i - строка, j - столобец
		{
			float Ai = 0; // сумма i ой строчки
			for (int j = 0; j < N; j++)
			{
				Ai += (*this)[i][j];
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
		float max_sum = std::numeric_limits<float>::lowest();
		for (int j = 0; j < N; j++) // i - строка, j - столобец
		{
			float Aj = 0; // сумма j ого столбца
			for (int i = 0; i < N; i++)
			{
				Aj += (*this)[i][j];
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
}
