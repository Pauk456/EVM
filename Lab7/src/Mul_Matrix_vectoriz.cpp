#include "Mul_matrix_vectoriz.h"

Matrix::Matrix(int N)
{
	this->N = N;
	matrix = new float[N * N];
	if (!matrix) 
	{
		exit(0);
	}
	for (int i = 0; i < N; i++) 
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

	__m128* mRes = (__m128*)Sum[0];
	__m128* mA = (__m128*)(*this)[0];
	__m128* mB = (__m128*)b[0];

	for (int i = 0; i < (N * N) / 4; i++)
	{
		mRes[i] = _mm_add_ps(mA[i], mB[i]);
	}
	for (int i = ((N * N) / 4) * 4; i < (N * N); i++)
	{
		int row = i / N;
		int col = i % N;
		Sum[row][col] = (*this)[row][col] + b[row][col];
	}
	return Sum;
}

Matrix& Matrix::operator+=(const Matrix& b) // Можно векторизовать
{
	__m128* mRes = (__m128*)(*this)[0];
	__m128* mA = (__m128*)(*this)[0];
	__m128* mB = (__m128*)b[0];

	for (int i = 0; i < (N * N) / 4; i++)
	{
		mRes[i] = _mm_add_ps(mA[i], mB[i]);
	}
	for (int i = ((N * N) / 4) * 4; i < (N * N); i++)
	{
		int row = i / N;
		int col = i % N;
		(*this)[row][col] = (*this)[row][col] + b[row][col];
	}

	return (*this);
}

Matrix Matrix::operator-(const Matrix& b) const// Можно векторизовать
{
	Matrix Sub(N);

	__m128* mRes = (__m128*)Sub[0];
	__m128* mA = (__m128*)(*this)[0];
	__m128* mB = (__m128*)b[0];

	for (int i = 0; i < (N * N) / 4; i++)
	{	
		mRes[i] = _mm_sub_ps(mA[i], mB[i]);
	}
	for (int i = ((N * N) / 4) * 4; i < (N * N); i++)
	{
		int row = i / N;
		int col = i % N;
		Sub[row][col] = (*this)[row][col] - b[row][col];
	}
	return Sub;
}

Matrix Matrix::operator*(const Matrix& b) const // Можно векторизовать
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
	__m128 *mRes = (__m128*)(*this)[0];
	__m128 mdivisor = _mm_set1_ps(b);
	for (int i = 0; i < (N * N) / 4; i++)
	{
		mRes[i] = _mm_div_ps(mRes[i], mdivisor);
	}
	for (int i = ((N * N) / 4) * 4; i < (N * N); i++)
	{
		int row = i / N;
		int col = i % N;
		(*this)[row][col] /=  b;
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

float Matrix::sum_max_row() // A8 // ФУНКЦИЯ РАБОТАЕТ ТОЛЬКО ДЛЯ ВЫРАВНЕННЫХ ДАННЫХ
{
	float max_sum = -9999999.0;
	for (int i = 0; i < N; i++) // i - строка, j - столобец
	{
		__m128 Ai = _mm_set1_ps(0);
		__m128* mV = (__m128*)(*this)[i];
		for (int j = 0; j < (N / 4); j++)
		{
			Ai = _mm_add_ps(Ai, mV[j]);
		}

		__m128 TAi = _mm_hadd_ps(Ai, Ai); // 1 + 2, 3 + 4, 1 + 2, 3 + 4,
		TAi = _mm_hadd_ps(TAi, TAi);
		float Ai_sum = 0;
		_mm_store_ss(&Ai_sum, TAi);

		for (int j = (N / 4) * 4; j < N; j++) {
			Ai_sum += (*this)[i][j];
		}

		if (Ai_sum > max_sum)
		{
			max_sum = Ai_sum;
		}
	}
	return max_sum;
}

float Matrix::sum_max_column() // A1 // Можно векторизовать
{
	float max_sum = -9999999.0;
	for (int j = 0; j < N; j++) // i - строка, j - столобец
	{
		float Aj = 0;
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
