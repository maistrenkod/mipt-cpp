#pragma once
#include<iostream>
#include<string>
#include <vector>

class Date
{
protected:
	int day, month;
	void correction();
public:
	Date();
	Date(const int x, const int y);
	void set_day(const int x);
	void set_month(const int y);
	int get_day();
	int get_month();
	friend Date operator+ (const Date& a, const Date& b);
	friend Date operator- (const Date& a, const Date& b);
};

class Date1 : public Date
{
protected:
	int year;
	void correction();
public:
	Date1();
	Date1(int x, int y, int z);
	void set_year(int z);
	int get_year();
	friend Date1 operator+(const Date1& a, const Date1& b);
	friend Date1 operator- (const Date1& a, const Date1& b);
};

template <typename T>
class Lessontime
{
	T date;
	std::vector<std::string> name;
public:
	Lessontime();
	Lessontime(T date, std::vector<std::string> names);
	void set_date(T date);
	void set_name(std::vector<std::string> names);
	void add_name(std::string name);
	T get_date();
	std::vector<std::string> get_name();
	template <typename T1>
	friend Lessontime<T1> operator+(const Lessontime<T1>& a, const Lessontime<T1>& b);
};

class Exception
{
private:
	int code;
	std::string description;
public:
	Exception(int code, const std::string description);
};

Exception::Exception(int code, const std::string description)
{
	this->code = code;
	this->description = description;
}

Date::Date()
{
	day = 0;
	month = 0;
}

Date::Date(const int x, const int y)
{
	day = x;
	month = y;
}

void Date::correction()
{
	while (day > 30)
	{
		day -= 30;
		month += 1;
	}
	while (day < 0)
	{
		day += 30;
		month -= 1;
	}
}

void Date::set_day(const int x)
{
	day = x;
}

void Date::set_month(const int y)
{
	month = y;
}

int Date::get_day()
{
	return day;
}

int Date::get_month()
{
	return month;
}

Date operator+(const Date& a, const Date& b)
{
	Date c;
	c.set_day(a.day + b.day);
	c.set_month(a.month + b.month);
	c.correction();
	return c;
}

Date operator-(const Date& a, const Date& b)
{
	Date c;
	c.set_day(a.day - b.day);
	c.set_month(a.month - b.month);
	c.correction();
	return c;
}

Date1 operator+(const Date1& a, const Date1& b)
{
	Date1 c;
	c.set_day(a.day + b.day);
	c.set_month(a.month + b.month);
	c.set_year(a.year + b.year);
	c.correction();
	return c;
}

Date1 operator-(const Date1& a, const Date1& b)
{
	Date1 c;
	c.set_day(a.day - b.day);
	c.set_month(a.month - b.month);
	c.set_year(a.year - b.year);
	c.correction();
	return c;
}

void Date1::correction()
{
	while (day > 30)
	{
		day -= 30;
		month += 1;
	}
	while (month > 12)
	{
		month -= 12;
		year += 1;
	}
	while (day < 0)
	{
		day += 30;
		month -= 1;
	}
	while (month < 0)
	{
		month += 12;
		year -= 1;
	}
}

Date1::Date1()
{
	day = 1;
	month = 1;
	year = 2020;
}

Date1::Date1(int x, int y, int z)
{
	day = x;
	month = y;
	year = z;
}

void Date1::set_year(int z)
{
	year = z;
}

int Date1::get_year()
{
	return year;
}

template<typename T>
Lessontime<T>::Lessontime()
{
	date = 0;
	std::vector<std::string> a;
	a.push_back("name");
	name = a;
}

template<typename T>
Lessontime<T>::Lessontime(T date, std::vector<std::string> names)
{
	try
	{
		for (int i = 0; i < names.size(); i++)
		{
			if (names[i].length() > 20) throw Exception(2, "Namelength\n");
		}
	}
	catch (const Exception& a)
	{
		std::cerr << "Name can't be more than 20 letters" << std::endl;
		exit(-1);
	}
	this->date = date;
	this->name = names;
}

template<typename T>
void Lessontime<T>::set_date(T date)
{
	this->date = date;
}

template<typename T>
void Lessontime<T>::set_name(std::vector<std::string> names)
{
	try
	{
		for (int i = 0; i < names.size(); i++)
		{
			if (names[i].length() > 20) throw Exception(3, "Namelength\n");
		}
	}
	catch (const Exception& a)
	{
		std::cerr << "Name can't be more than 20 letters" << std::endl;
		exit(-1);
	}
	this->name = names;
}

template<typename T>
void Lessontime<T>::add_name(std::string name)
{
	try
	{
		if (name.length() > 20) throw Exception(4, "Namelength\n");
	}
	catch (const Exception& a)
	{
		std::cerr << "Name can't be more than 20 letters" << std::endl;
		exit(-1);
	}
	this->name.push_back(name);
}

template<typename T>
T Lessontime<T>::get_date()
{
	return date;
}

template<typename T>
std::vector<std::string> Lessontime<T>::get_name()
{
	return name;
}

template<typename T1>
Lessontime<T1> operator+(const Lessontime<T1>& a, const Lessontime<T1>& b)
{
	Lessontime<T1> c;
	c.name = a.name;
	c.set_date(a.date + b.date);
	return c;
}
