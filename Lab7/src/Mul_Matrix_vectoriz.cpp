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

	__m128* mRes0 = (__m128*)Sum[0];
	__m128* mA = (__m128*)(*this)[0];
	__m128* mB = (__m128*)b[0];

	for (int i = 0; i < (N * N) / 4; i += 1)
	{
		mRes0[i] = _mm_add_ps(mA[i], mB[i]);
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
	return Sub;
}

Matrix Matrix::operator*(const Matrix& b) const // Можно векторизовать 
{
	Matrix Mul(N); // i - строка, j - столбе
	for (int row1 = 0; row1 < N; row1 += 4)
	{
		float* str0 = (float*)(*this)[row1];
		float* str1 = (float*)(*this)[row1 + 1];
		float* str2 = (float*)(*this)[row1 + 2];
		float* str3 = (float*)(*this)[row1 + 3];
		for (int col2 = 0; col2 < N; col2 += 16)
		{
			__m128 mSum00 = _mm_set1_ps(0);
			__m128 mSum01 = _mm_set1_ps(0);
			__m128 mSum02 = _mm_set1_ps(0);
			__m128 mSum03 = _mm_set1_ps(0);
			__m128 mSum10 = _mm_set1_ps(0);
			__m128 mSum11 = _mm_set1_ps(0);
			__m128 mSum12 = _mm_set1_ps(0);
			__m128 mSum13 = _mm_set1_ps(0);
			__m128 mSum20 = _mm_set1_ps(0);
			__m128 mSum21 = _mm_set1_ps(0);
			__m128 mSum22 = _mm_set1_ps(0);
			__m128 mSum23 = _mm_set1_ps(0);
			__m128 mSum30 = _mm_set1_ps(0);
			__m128 mSum31 = _mm_set1_ps(0);
			__m128 mSum32 = _mm_set1_ps(0);
			__m128 mSum33 = _mm_set1_ps(0);
			for (int col1 = 0; col1 < N; col1++)
			{
				__m128 mBstr0 = _mm_loadu_ps(&b[col1][col2]);
				__m128 mBstr1 = _mm_loadu_ps(&b[col1][col2 + 4]);
				__m128 mBstr2 = _mm_loadu_ps(&b[col1][col2 + 8]);
				__m128 mBstr3 = _mm_loadu_ps(&b[col1][col2 + 12]);
				__m128 mMul0 = _mm_set1_ps(str0[col1]);
				__m128 mMul1 = _mm_set1_ps(str1[col1]);
				__m128 mMul2 = _mm_set1_ps(str2[col1]);
				__m128 mMul3 = _mm_set1_ps(str3[col1]);
				mSum00 = _mm_add_ps(mSum00, _mm_mul_ps(mMul0, mBstr0));
				mSum01 = _mm_add_ps(mSum01, _mm_mul_ps(mMul0, mBstr1));
				mSum02 = _mm_add_ps(mSum02, _mm_mul_ps(mMul0, mBstr2));
				mSum03 = _mm_add_ps(mSum03, _mm_mul_ps(mMul0, mBstr3));
				mSum10 = _mm_add_ps(mSum10, _mm_mul_ps(mMul1, mBstr0));
				mSum11 = _mm_add_ps(mSum11, _mm_mul_ps(mMul1, mBstr1));
				mSum12 = _mm_add_ps(mSum12, _mm_mul_ps(mMul1, mBstr2));
				mSum13 = _mm_add_ps(mSum13, _mm_mul_ps(mMul1, mBstr3));
				mSum20 = _mm_add_ps(mSum20, _mm_mul_ps(mMul2, mBstr0));
				mSum21 = _mm_add_ps(mSum21, _mm_mul_ps(mMul2, mBstr1));
				mSum22 = _mm_add_ps(mSum22, _mm_mul_ps(mMul2, mBstr2));
				mSum23 = _mm_add_ps(mSum23, _mm_mul_ps(mMul2, mBstr3));
				mSum30 = _mm_add_ps(mSum30, _mm_mul_ps(mMul3, mBstr0));
				mSum31 = _mm_add_ps(mSum31, _mm_mul_ps(mMul3, mBstr1));
				mSum32 = _mm_add_ps(mSum32, _mm_mul_ps(mMul3, mBstr2));
				mSum33 = _mm_add_ps(mSum33, _mm_mul_ps(mMul3, mBstr3));
			}
			_mm_storeu_ps(&Mul[row1][col2], mSum00);
			_mm_storeu_ps(&Mul[row1][col2 + 4], mSum01);
			_mm_storeu_ps(&Mul[row1][col2 + 8], mSum02);
			_mm_storeu_ps(&Mul[row1][col2 + 12], mSum03);
			_mm_storeu_ps(&Mul[row1 + 1][col2], mSum10);
			_mm_storeu_ps(&Mul[row1 + 1][col2 + 4], mSum11);
			_mm_storeu_ps(&Mul[row1 + 1][col2 + 8], mSum12);
			_mm_storeu_ps(&Mul[row1 + 1][col2 + 12], mSum13);
			_mm_storeu_ps(&Mul[row1 + 2][col2], mSum20);
			_mm_storeu_ps(&Mul[row1 + 2][col2 + 4], mSum21);
			_mm_storeu_ps(&Mul[row1 + 2][col2 + 8], mSum22);
			_mm_storeu_ps(&Mul[row1 + 2][col2 + 12], mSum23);
			_mm_storeu_ps(&Mul[row1 + 3][col2], mSum30);
			_mm_storeu_ps(&Mul[row1 + 3][col2 + 4], mSum31);
			_mm_storeu_ps(&Mul[row1 + 3][col2 + 8], mSum32);
			_mm_storeu_ps(&Mul[row1 + 3][col2 + 12], mSum33);
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
		float Ai_sum;
		_mm_store_ss(&Ai_sum, TAi);

		if (Ai_sum > max_sum)
		{
			max_sum = Ai_sum;
		}
	}
	return max_sum;
}

float Matrix::sum_max_column() // A1 // Можно векторизовать
{
	__m128 mMax_sum = _mm_set_ps(
		std::numeric_limits<float>::min(), 
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min());
	for (int j = 0; j < N; j += 16) // i - строка, j - столобец
	{
		__m128 mSum0 = _mm_set1_ps(0);
		__m128 mSum1 = _mm_set1_ps(0);
		__m128 mSum2 = _mm_set1_ps(0);
		__m128 mSum3 = _mm_set1_ps(0);
		for (int i = 0; i < N; i++)
		{
			__m128 mStr0 = _mm_loadu_ps(&(*this)[i][j]);
			__m128 mStr1 = _mm_loadu_ps(&(*this)[i][j + 4]);
			__m128 mStr2 = _mm_loadu_ps(&(*this)[i][j + 8]);
			__m128 mStr3 = _mm_loadu_ps(&(*this)[i][j + 12]);
			mSum0 = _mm_add_ps(mSum0, mStr0);
			mSum1 = _mm_add_ps(mSum1, mStr1);
			mSum2 = _mm_add_ps(mSum2, mStr2);
			mSum3 = _mm_add_ps(mSum3, mStr3);
		}
		__m128 max1 = _mm_max_ps(mSum0, mSum1); // _mm_max_ps(4 1 2 3, 1 2 5 8) = 4 2 5 8 
		__m128 max2 = _mm_max_ps(mSum2, mSum3); 
		__m128 result = _mm_max_ps(max1, max2);
		mMax_sum = _mm_max_ps(mMax_sum, result);
	}

	float max_sum_float = std::numeric_limits<float>::min();
	float Max_sum_float[4];
	_mm_storeu_ps(Max_sum_float, mMax_sum);
	for (int i = 0; i < 4; i++)
	{
		if (Max_sum_float[i] > max_sum_float)
		{
			max_sum_float = Max_sum_float[i];
		}
	}
	return max_sum_float;
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
