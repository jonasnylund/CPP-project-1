#ifndef MATRIX_HPP
#define MATRIX_HPP


class Matrix {
public:
	static Matrix eye(const unsigned int);
	static Matrix random(const unsigned int);
	static Matrix random(const unsigned int, const unsigned int);

	Matrix(int m);
	Matrix(int m, int n);
	Matrix(const Matrix&);
	~Matrix();
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator+=(const double);
	Matrix& operator-=(const Matrix&);
	friend Matrix operator+(const Matrix&, const Matrix&);
	friend Matrix operator-(const Matrix&, const Matrix&);
	Matrix& operator*=(const Matrix&);
	friend Matrix operator*(const Matrix&, const Matrix&);
	Matrix& operator*=(const double);
	Matrix& operator/=(const double);

	double* operator[](unsigned int i) const;
	Matrix exp(const double tol=1e-10) const;
	Matrix transpose() const;
	double norm() const;
	void print() const;
	void fillMatrix(
		double array[],
		unsigned int lx,
		unsigned int ly,
		unsigned int ox,
		unsigned int oy);

	double* getArray();

private:

	double* array;
	unsigned int rows;
	unsigned int cols;

	inline unsigned int index(unsigned int i, unsigned int j) const;

};

#endif