#pragma once
#include <vector>
#include <iostream>

class Matrix 
{
private:
	int N;
	std::vector< std::vector<float> > matrix;
private:
	Matrix calculate_R(Matrix& B);
	Matrix calculate_B();
	float sum_max_row();
	float sum_max_column();
public:
	Matrix(int N);
	void reverse_matrix(int M);
	Matrix transpose_matrix() const;
	void to_single();

	std::vector<float>& operator[](int row) 
	{
		return matrix[row];
	}
	const std::vector<float>& operator[](int row) const 
	{
		return matrix[row];
	}
	Matrix operator+(const Matrix& b) const;
	Matrix& operator+=(const Matrix& b);
	Matrix operator-(const Matrix& b) const;
	Matrix operator*(const Matrix& b) const;
	Matrix& operator/(const float b);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);
};

