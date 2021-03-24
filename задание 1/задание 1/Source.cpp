#include "Header.h"
#include <iostream>
#include<vector>
#include<string>

int main()
{
	Date a(28, 3);
	Date b(5, 2);
	Date c;
	c = a + b;
	std::cout << c.get_day() << "." << c.get_month() << std::endl;
	c = b - a;
	std::cout << c.get_day() << "." << c.get_month() << std::endl;

	Date1 m(28, 12, 2001);
	Date1 n(5, 3, 2);
	Date1 k;
	k = m + n;
	std::cout << k.get_day() << "." << k.get_month() << "." << k.get_year() << std::endl;
	k = m - n;
	std::cout << k.get_day() << "." << k.get_month() << "." << k.get_year() << std::endl;

	Lessontime<int> s;
	s.set_date(2003);
	std::vector<std::string> str;
	str.push_back("Petya");
	str.push_back("Kolya");
	str.push_back("Vasya");
	Lessontime<int> p(2004, str);
	Lessontime<int> o;
	s.set_name(str);
	o = s + p;
	std::cout << o.get_date() << "   " << o.get_name()[0];
	return 0;
}