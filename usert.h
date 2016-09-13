#ifndef USERT_H
#define USERT_H
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class UserT
{
private:
	char type_[10];	//teach or stud
protected:
	char name_[40];
	virtual void print(ostream& sout) const = 0;
public:
	UserT(string type, string name = "")
	{ 
		strcpy(name_, name.c_str()); 
		strcpy(type_, type.c_str());
	}

	virtual ~UserT() {}
	
	// аксессоры
	char* name() { return name_; }
	char* type() { return type_; }
	// виртуальные аксессоры Для наследников
	virtual char* password() const { return ""; }
	virtual char* ID() const { return ""; }
	virtual int grade() const { return 0; }

	//функции для записи в dat-файл
	virtual void save(fstream& of) = 0;
	virtual void load(fstream& inf) = 0;
	
	//для вывода на консоль и для текстовых файлов
	friend ostream& operator<<(ostream& sout, UserT * u)
	{
		u->print(sout);
		return sout;
	}
	
	//операторы сравнения нужны для вставки в сет из указателей в классе Manager
	//вот только для поиска не по всем полям не работает, поэтому find_by_name (manager.h), а эти пусть уж будут
	friend bool operator<(UserT &left, UserT &right) 
	{ 
		if (strcmp(left.name(), right.name()) < 0)
			return true;
		else
			return false;
	}
	friend bool operator==(UserT &left, UserT &right)
	{
		if (strcmp(left.name(), right.name()) == 0)
			return true;
		else
			return false;
	}

};

#endif