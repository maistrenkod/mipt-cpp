#include "Header.h"
#include <iostream>

int main()
{
	Human *ivan = new Human();
	std::cout << ivan->get_name() << "  " << ivan->get_age() << "\n";
	Student* vova = new Student();
	std::cout << vova->get_name() << "  " << vova->get_age() << "  " << vova->get_score() << "\n";
	Teacher* petya = new Teacher("Petya", 35, 500000);
	std::cout << petya->get_name() << "  " << petya->get_age() << "  " << petya->get_sal() << "\n";
	return 0;
}