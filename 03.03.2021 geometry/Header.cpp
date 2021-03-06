#include "Header.h"
#include <math.h>
#define M_PI 3.14159265358979323846

void Circle::set_coordinates(double x, double y, double R)
{
	this->x = x;
	this->y = y;
	this->R = R;
}

double Circle::get_x()
{
	return this->x;
}

double Circle::get_y()
{
	return this->y;
}

double Circle::get_R()
{
	return this->R;
}

std::string Circle::perimeter()
{
	return "circle" + std::to_string(2*M_PI*this->R);
}

double Circle::area()
{

	return M_PI * this->R * this->R;
}

void Triangle::set_coordinates(double x1, double x2, double x3, double y1, double y2, double y3)
{
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
}

double Triangle::get_x1()
{
	return this->x1;
}

double Triangle::get_x2()
{
	return this->x2;
}

double Triangle::get_x3()
{
	return this->x3;
}

double Triangle::get_y1()
{
	return this->y1;
}

double Triangle::get_y2()
{
	return this->y2;
}

double Triangle::get_y3()
{
	return this->y3;
}

std::string Triangle::perimeter()
{
	double a = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	double c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
	return "triangle" + std::to_string(a + b + c);
}

double Triangle::area()
{
	double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	double c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
	double p = (a + b + c) / 2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}

void Quadrilateral::set_coordinates(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4)
{
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->x4 = x4;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->y4 = y4;
}

double Quadrilateral::get_x1()
{
	return this->x1;
}

double Quadrilateral::get_x2()
{
	return this->x2;
}

double Quadrilateral::get_x3()
{
	return this->x3;
}

double Quadrilateral::get_x4()
{
	return this->x4;
}

double Quadrilateral::get_y1()
{
	return this->y1;
}

double Quadrilateral::get_y2()
{
	return this->y2;
}

double Quadrilateral::get_y3()
{
	return this->y3;
}

double Quadrilateral::get_y4()
{
	return this->y4;
}

std::string Quadrilateral::perimeter()
{
	double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	double c = sqrt((x1 - x4) * (x1 - x4) + (y1 - y4) * (y1 - y4));
	double d = sqrt((x3 - x4) * (x3 - x4) + (y3 - y4) * (y3 - y4));
	return "quadrilateral" + std::to_string(a + b + c + d);
}

double Quadrilateral::area()
{
	Triangle* c = new Triangle();
	c->set_coordinates(x1, x2, x3, y1, y2, y3);
	Triangle* d = new Triangle();
	d->set_coordinates(x1, x4, x3, y1, y4, y3);
	return c->area() + d->area();
}

std::string Rectangle::perimeter()
{
	double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	return "rectangle" + std::to_string(2 * (a + b));
}

double Rectangle::area()
{
	double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	return a * b;
}

bool Square::is_Square()
{
	double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	double c = sqrt((x1 - x4) * (x1 - x4) + (y1 - y4) * (y1 - y4));
	double d = sqrt((x3 - x4) * (x3 - x4) + (y3 - y4) * (y3 - y4));
	if (a == b && a == c && a == d) return true;
	else return false;
}

std::string Square::perimeter()
{
	double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return "square" + std::to_string(4 * a);
}

double Square::area()
{
	double a = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	return a;
}
