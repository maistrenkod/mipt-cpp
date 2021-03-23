#include"Header.h"
#include<iostream>
#include<array>

int main()
{
	/*Vector2D<int, 5> t(8);
	std::cin >> t;
	Vector2D<int, 5> q(7);
	std::cout << t + q << std::endl;
	std::cout << t - q << std::endl;
	std::cout << t * q << std::endl;
	//std::cout << (t ^ q) << std::endl;
	std::cout << (t == q) << std::endl;
	std::cout << (t != q) << std::endl;
	std::cout << (t > q) << std::endl;
	std::cout << (t < q) << std::endl;*/

	Matrix<int, 3, 3> a(9);
	Matrix<int, 3, 3> d(3);
	std::cout << a + d << std::endl;
	std::cout << a - d << std::endl;
	std::cout << a * d << std::endl;
	std::cout << (a == d) << std::endl;
	a.set_x_ij(7, 2, 1);
	std::cout << a << std::endl;
	std::cout << tr(a) << std::endl;

	return 0;
}