#pragma once
#include <string>
#include <iostream>
#include <sstream>

template<typename T, int n>
class Vector2D
{
	T x[n];
public:
	Vector2D();
	Vector2D(T a);
	Vector2D(T a, int i);
	void set_x_i(T a, int i);
	T get_x_i(int i) const;
	template<typename T1, int n1>
	friend Vector2D<T1, n1> operator+ (const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b);
	template<typename T1, int n1>
	friend Vector2D<T1, n1> operator- (const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b);
	template<typename T1, int n1>
	friend T1 operator* (const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b);
	template<typename T1, int n1>
	friend Vector2D<T1, n1> operator* (const double& a, const Vector2D<T1, n1>& b);
	template<typename T1, int n1>
	friend Vector2D<T1, n1> operator^ (const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b);
	template<typename T1, int n1>
	friend bool operator== (const Vector2D<T1, n1> a, const Vector2D<T1, n1> b);
	template<typename T1, int n1>
	friend bool operator!= (const Vector2D<T1, n1> a, const Vector2D<T1, n1> b);
	template<typename T1, int n1>
	friend bool operator> (const Vector2D<T1, n1> a, const Vector2D<T1, n1> b);
	template<typename T1, int n1>
	friend bool operator< (const Vector2D<T1, n1> a, const Vector2D<T1, n1> b);
	template<typename T1, int n1>
	friend std::ostream& operator<< (std::ostream& out, const Vector2D<T1, n1>& a);
	template<typename T1, int n1>
	friend std::istream& operator>> (std::istream& in, Vector2D<T1, n1>& a);
};

template<typename T, int m, int n>
class Matrix
{
	T x[m][n];
public:
	Matrix();
	Matrix(T a);
	void set_x_ij(T a, int i, int j);
	T get_x_ij(int i, int j) const;
	template<typename T1, int m1, int n1>
	friend Matrix<T1, m1, n1> operator+ (const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b);
	template<typename T1, int m1, int n1>
	friend Matrix<T1, m1, n1> operator- (const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b);
	template<typename T1, int m1, int n1>
	friend Matrix<T1, m1, n1> operator* (const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b);
	template<typename T1, int m1, int n1>
	friend Matrix<T1, m1, n1> tr(Matrix<T1, m1, n1>& a);
	template<typename T1, int m1, int n1>
	friend bool operator== (const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b);
	template<typename T1, int m1, int n1>
	friend bool operator!= (const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b);
	template<typename T1, int m1, int n1>
	friend std::ostream& operator<< (std::ostream& out, const Matrix<T1, m1, n1>& a);
	template<typename T1, int m1, int n1>
	friend std::istream& operator>> (std::istream& in, Matrix<T1, m1, n1>& a);
};

class Exception
{
private:
	int code;
	std::string description;
public:
	Exception(int code, const std::string description);
};

template<typename T, int n>
Vector2D<T, n>::Vector2D<T, n>()
{
	for (int i = 0; i < n; i++)
	{
		x[i] = 0;
	}
}

template<typename T, int n>
Vector2D<T, n>::Vector2D<T, n>(T a)
{
	for (int i = 0; i < n; i++)
	{
		x[i] = a;
	}
}

template<typename T, int n>
Vector2D<T, n>::Vector2D(T a, int i)
{
	for (int j = 0; j < i; j++)
	{
		x[j] = 0;
	}
	x[i] = a;
	for (int j = i + 1; j < n; j++)
	{
		x[j] = 0;
	}
}

template<typename T, int n>
void Vector2D<T, n>::set_x_i(T a, int i)
{
	x[i] = a;
}

template<typename T, int n>
T Vector2D<T, n>::get_x_i(int i) const
{
	return x[i];
}

template<typename T1, int n1>
Vector2D<T1, n1> operator+(const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b)
{
	Vector2D<T1, n1> c;
	for (int i = 0; i < n1; i++)
	{
		c.set_x_i(a.get_x_i(i) + b.get_x_i(i), i);
	}
	return c;
}

template<typename T1, int n1>
Vector2D<T1, n1> operator-(const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b)
{
	Vector2D<T1, n1> c;
	for (int i = 0; i < n1; i++)
	{
		c.set_x_i(a.get_x_i(i) - b.get_x_i(i), i);
	}
	return c;
}

template<typename T1, int n1>
T1 operator*(const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b)
{
	double c = 0;
	for (int i = 0; i < n1; i++)
	{
		c += a.get_x_i(i) * b.get_x_i(i);
	}
	return c;
}

template<typename T1, int n1>
Vector2D<T1, n1> operator*(const double& a, const Vector2D<T1, n1>& b)
{
	Vector2D<T1, n1> c;
	for (int i; i < n1; i++)
	{
		c.set_x_i(a * b.get_x_i(i), i);
	}
	return c;
}

template<typename T1, int n1>
Vector2D<T1, n1> operator^(const Vector2D<T1, n1>& a, const Vector2D<T1, n1>& b)
{
	try
	{
		if (n1 != 3) throw Exception(1, "Error");
		Vector2D<T1, n1> c;
		c.set_x_i(a.get_x_i(2) * b.get_x_i(3) - a.get_x_i(3) * b.get_x_i(2), 1);
		c.set_x_i(a.get_x_i(3) * b.get_x_i(1) - a.get_x_i(1) * b.get_x_i(3), 2);
		c.set_x_i(a.get_x_i(1) * b.get_x_i(2) - a.get_x_i(2) * b.get_x_i(1), 3);
		return c;
	}
	catch (const Exception& a)
	{
		std::cerr << "Error\n";
		exit(-1);
	}
}

template<typename T1, int n1>
bool operator==(const Vector2D<T1, n1> a, const Vector2D<T1, n1> b)
{
	if (a.get_x_i(1) == b.get_x_i(1) && a.get_x_i(2) == b.get_x_i(2) && a.get_x_i(3) == b.get_x_i(3)) return true;
	else return false;
}

template<typename T1, int n1>
bool operator!=(const Vector2D<T1, n1> a, const Vector2D<T1, n1> b)
{
	if (a.get_x_i(1) == b.get_x_i(1) && a.get_x_i(2) == b.get_x_i(2) && a.get_x_i(3) == b.get_x_i(3)) return false;
	else return true;
}

template<typename T1, int n1>
bool operator>(const Vector2D<T1, n1> a, const Vector2D<T1, n1> b)
{
	double a1 = 0;
	double b1 = 0;
	for (int i = 0; i < n1; i++)
	{
		a1 += a.get_x_i(i) * a.get_x_i(i);
		b1 += b.get_x_i(i) * b.get_x_i(i);
	}
	if (a1 > b1) return true;
	else return false;
}

template<typename T1, int n1>
bool operator<(const Vector2D<T1, n1> a, const Vector2D<T1, n1> b)
{
	if (a > b || a == b) return false;
	else return true;
}

template<typename T1, int n1>
std::ostream& operator<<(std::ostream& out, const Vector2D<T1, n1>& a)
{
	for (int i = 0; i < n1; i++)
	{
		out << a.get_x_i(i) << " ";
	}
	return out;
}

template<typename T1, int n1>
std::istream& operator>>(std::istream& in, Vector2D<T1, n1>& a)
{
	T1 k;
	for (int i = 0; i < n1; i++)
	{
		in >> k;
		a.set_x_i(k, i);
	}
	return in;
}

Exception::Exception(int code, const std::string description)
{
	this->code = code;
	this->description = description;
}

template<typename T1, int m1, int n1>
Matrix<T1, m1, n1> operator+(const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b)
{
	Matrix<T1, m1, n1> c;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			c.set_x_ij(a.get_x_ij(i, j) + b.get_x_ij(i, j), i, j);
		}
	}
	return c;
}

template<typename T1, int m1, int n1>
Matrix<T1, m1, n1> operator-(const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b)
{
	Matrix<T1, m1, n1> c;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			c.set_x_ij(a.get_x_ij(i, j) - b.get_x_ij(i, j), i, j);
		}
	}
	return c;
}

template<typename T1, int m1, int n1>
Matrix<T1, m1, n1> operator*(const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b)
{
	try
	{
		if (n1 != m1) throw 1;
	}
	catch (int a)
	{
		std::cerr << "invalid Matrix size\n";
	}
	Matrix<T1, m1, n1> c;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			for (int k = 0; k < n1; k++)
			{
				c.set_x_ij(a.get_x_ij(i, k) * a.get_x_ij(k, j), i, j);
			}
		}
	}
	return c;
}

template<typename T1, int m1, int n1>
Matrix<T1, m1, n1> tr(Matrix<T1, m1, n1>& a)
{
	Matrix<T1, n1, m1> c;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			c.set_x_ij(a.get_x_ij(j, i), i, j);
		}
	}
	return c;
}

template<typename T1, int m1, int n1>
bool operator==(const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b)
{
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			if (b.get_x_ij(i, j) != a.get_x_ij(i, j)) return false;
		}
	}
	return true;
}

template<typename T1, int m1, int n1>
bool operator!=(const Matrix<T1, m1, n1>& a, const Matrix<T1, m1, n1>& b)
{
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			if (b.get_x_ij(i, j) == a.get_x_ij(i, j)) return false;
		}
	}
	return true;
}

template<typename T1, int m1, int n1>
std::ostream& operator<<(std::ostream& out, const Matrix<T1, m1, n1>& a)
{
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			out << a.get_x_ij(i, j) << " ";
		}
		out << std::endl;
	}
	return out;
}

template<typename T1, int m1, int n1>
std::istream& operator>>(std::istream& in, Matrix<T1, m1, n1>& a)
{
	T1 k;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			in >> k;
			a.set_x_ij(k, i, j);
		}
	}
	return in;
}

template<typename T, int m, int n>
Matrix<T, m, n>::Matrix()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			x[i][j] = 0;
		}
	}
}

template<typename T, int m, int n>
Matrix<T, m, n>::Matrix(T a)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			x[i][j] = a;
		}
	}
}

template<typename T, int m, int n>
void Matrix<T, m, n>::set_x_ij(T a, int i, int j)
{
	x[i][j] = a;
}

template<typename T, int m, int n>
T Matrix<T, m, n>::get_x_ij(int i, int j) const
{
	return x[i][j];
}