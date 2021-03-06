#include"Header.h"
#include <iostream>

int main()
{
	Triangle* a = new Triangle();
	a->set_coordinates(1, 2, 2, 1, 1, 2);
	std::cout << "area " << a->area() << "\nperimeter " << a->perimeter() << "\n";
	Circle* b = new Circle();
	b->set_coordinates(0, 0, 5);
	std::cout << "area " << b->area() << "\nperimeter " << b->perimeter() << "\n";
	Quadrilateral* c = new Square();
	c->set_coordinates(0, 1, 1, 0, 0, 0, 1, 1);
	std::cout << "area " << c->area() << "\nperimeter " << c->perimeter() << "\n";
	return 0;
}