//интерфейс класса Student
#ifndef STUDENT_H
#define STUDENT_H
#include "../usert.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Student : public UserT
{
public:
	Student(string name = "", string id = "", int grade = 0) : UserT("Student", name), grade_(grade) { strcpy(ID_, id.c_str()); }
	~Student() {}
	virtual char* ID() { return ID_; }
	virtual int grade() { return grade_; }
	void set_grade(int grade) { grade_ = grade; }

	//функции для записи в dat-файл
	virtual void save(fstream& of)
	{
		of.write(type(), 10);
		of.write(name_, sizeof(name_));
		of.write(ID_, sizeof(ID_));
		of.write(reinterpret_cast<const char *>(&grade_), sizeof(grade_));
	}
	virtual void load(fstream& inf)
	{
		inf.read(name_, sizeof(name_));
		inf.read(ID_, sizeof(ID_));
		inf.read(reinterpret_cast<char *>(&grade_), sizeof(grade_));
	}

protected:
	virtual void print(ostream& sout) const 
	{
		sout << "Student\n" << name_ << " " << ID_ << " "<< grade_ << endl;
	}

private:
	//char name_[50];
	char ID_[10];
	int grade_;
};

#endif