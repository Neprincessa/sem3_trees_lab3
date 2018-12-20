#ifndef __STUDENT_IMPL_
#define __STUDENT_IMPL_

#include <string>
#include <iostream>
//#include <ostream>

using namespace std;

class Student {
public:
	string name;
	int age;
	int flag;

	Student(string name, int x) {
		this->name = name;
		this->age = x;
	}

	Student () {}
	~Student() {}

	void set_student(string s, int a) {
		name = s;
		age = a;
	}
	void set_flag(int flag) {
		this->flag = flag;
	}

	bool operator==(const Student &student1) {
		if (flag == 1) return (name == student1.name);
		else return (age == student1.age);
	}
	bool operator>(const Student &student1) {
		if (flag == 1) return (name > student1.name);
		else return (age > student1.age);
	}
	bool operator<(const Student &student1) {
		if (flag == 1) return (name < student1.name);
		else return (age < student1.age);
	}
	bool operator<=(const Student &student1) {
		if (flag == 1) return (name <= student1.name);
		else return (age <= student1.age);
	}
	bool operator>=(const Student &student1) {
		if (flag == 1) return (name >= student1.name);
		else return (age >= student1.age);
	}
	bool operator!=(const Student &student1) {
		if (flag == 1) return (name != student1.name);
		else return (age != student1.age);
	}
	void printSudent() {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
	}
	friend std::ostream &operator<<(std::ostream &os, const Student &student) {

			if (student.flag == 1) return os << student.name;
			else return os << student.age;
			//os << student.name << " " << student.age;
			//return os;
	}
	int get_flag() {
		return flag;
	}
	string get_name() {
		return name;
	}
	int get_age() {
		return age;
	}
};




#endif // !__STUDENT_IMPL_

