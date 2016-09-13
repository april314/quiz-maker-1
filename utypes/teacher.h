#ifndef TEACHER_H
#define TEACHER_H
#include <fstream>
#include <string>
#include <set>
#include "../usert.h"
using namespace std;

class Teacher : public UserT
{
public:
	Teacher(string name = "", string password = "") : UserT("Teacher", name) { strcpy(password_, password.c_str()); }
	~Teacher() {}
	virtual char* password() 	{ return password_; }
	void set_password(const string & pswd) { strcpy(password_, pswd.c_str()); }

	virtual void print (ostream& sout) const 
	{
		sout << "Teacher\n" << name_ << password_ << endl;
	}

	//функции для записи в dat-файл
	virtual void save(fstream& of)
	{
		of.write(type(), 10);
		of.write(name_, sizeof(name_));
		of.write(password_, sizeof(password_));
	}
	virtual void load(fstream& inf)
	{
		inf.read(name_, sizeof(name_));
		inf.read(password_, sizeof(password_));
	}

private:
	//char name_[];
	char password_[20];
};

#endif