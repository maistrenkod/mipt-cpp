#include "Header.h"

Human::Human()
{
	name = "Ivan";
	age = 18;
}

Human::Human(std::string name, int age)
{
	this->name = name;
	this->age = age;
}

std::string Human::get_name()
{
	return this->name;
}

int Human::get_age()
{
	return this->age;
}

void Human::set_name(std::string name)
{
	this->name = name;
}

void Human::set_age(int age)
{
	this->age = age;
}

Student::Student(std::string name, int age, int score):Human(name, age)
{
	this->score = 10;
}

Student::Student() : Human()
{
	this->score = 10;
}

void Student::set_score(int score)
{
	this->score = score;
}

int Student::get_score()
{
	return this->score;
}

Teacher::Teacher(std::string name, int age, int salary):Human(name, age)
{
	this->salary = salary;
}

Teacher::Teacher() : Human()
{
	this->salary = 1000;
}

void Teacher::set_sal(int salary)
{
	this->salary = salary;
}

int Teacher::get_sal()
{
	return this->salary;
}
