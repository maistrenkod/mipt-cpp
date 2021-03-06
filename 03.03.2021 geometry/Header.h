#include<string>

class Figure
{
public:
	virtual std::string perimeter() = 0;
	virtual double area() = 0;
};

class Circle : public Figure
{
protected:
	double x, y, R;
public:
	void set_coordinates(double x, double y, double R);
	double get_x();
	double get_y();
	double get_R();
	std::string perimeter();
	double area();
};

class Triangle : public Figure
{
protected:
	double x1, x2, x3, y1, y2, y3;
public:
	void set_coordinates(double x1, double x2, double x3, double y1, double y2, double y3);
	double get_x1();
	double get_x2();
	double get_x3();
	double get_y1();
	double get_y2();
	double get_y3();
	std::string perimeter();
	double area();
};

class Quadrilateral : public Figure
{
protected:
	double x1, x2, x3, x4, y1, y2, y3, y4;
public:
	void set_coordinates(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4);
	double get_x1();
	double get_x2();
	double get_x3();
	double get_x4();
	double get_y1();
	double get_y2();
	double get_y3();
	double get_y4();
	std::string perimeter();
	virtual double area();
};

class Rectangle : public Quadrilateral
{
	virtual std::string perimeter();
	virtual double area();
};

class Square : public Rectangle
{
	bool is_Square();
	std::string perimeter();
	double area();
};