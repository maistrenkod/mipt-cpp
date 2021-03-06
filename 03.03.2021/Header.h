#include <string>

class  Human
{
protected:
	std::string name;
	int age;
public:
	Human();
	Human(std::string name, int age);
	std::string get_name();
	int get_age();
	void set_name(std::string name);
	void set_age(int age);
	virtual int get();

};

class Student: public Human
{
protected:
	int score;
public:
	Student(std::string name, int age, int score);
	Student();
	void set_score(int score);
	int get_score();
};

class Teacher : public Human
{
protected: 
	int salary;
public:
	Teacher(std::string name, int age, int salary);
	Teacher();
	void set_sal(int salary);
	int get_sal();
};