#include "Matrix_BLAS.h"

namespace Matrix_blas
{
	Matrix::Matrix(int N)
	{
		this->N = N;
		matrix = new float[N * N];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				(*this)[i][j] = 0;
			}
		}
	}

	Matrix::~Matrix() {
		delete matrix;
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

	template <typename Mat>
	void Matrix::copy(Mat& copy)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				(*this)[i][j] = copy[i][j];
			}
		}
	}

	Matrix Matrix::operator+(const Matrix& b) const
	{
		Matrix Sum(N);
		// ����������� ������ �� ������� ������� � Sum
		cblas_scopy(N * N, (*this)[0], 1, Sum[0], 1);
		// �������� � �������� b
		cblas_saxpy(N * N, 1.0f, b[0], 1, Sum[0], 1);
		return Sum;
	}

	Matrix& Matrix::operator+=(const Matrix& b)
	{
		cblas_saxpy(N * N, 1.0, b[0], 1, (*this)[0], 1);
		return (*this);
	}

	Matrix Matrix::operator-(const Matrix& b) const
	{
		Matrix Diff(N);
		// ����������� ������ �� ������� ������� � Diff
		cblas_scopy(N * N, (*this)[0], 1, Diff[0], 1);
		// ��������� ������� b
		cblas_saxpy(N * N, -1.0f, b[0], 1, Diff[0], 1);
		return Diff;
	}

	Matrix Matrix::operator*(const Matrix& b) const
	{
		Matrix Mul(N); // i - ������, j - �������
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, b[0], N, (*this)[0], N, 0.0, Mul[0], N);
		return Mul;
	}

	Matrix& Matrix::operator/(const float b)
	{
		cblas_sscal(N * N, 1.0f / b, (*this)[0], 1);
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
		for (int i = 0; i < N; i++) // i - ������, j - ��������
		{
			float Ai = cblas_sasum(N, (*this)[i], 1); // ����� i �� �������

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
		for (int j = 0; j < N; j++) // i - ������, j - ��������
		{
			float Aj = 0; // ����� j ��� �������
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
