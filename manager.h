#ifndef MANAGER_H
#define MANAGER_H
#include <set>
#include <string>
#include <fstream>
#include "tests.h"
#include "usert.h"
#include "utypes/student.h"
using namespace std;

class Manager
{
public:
	Manager(const string& usersfile = "users");
	~Manager();
	
	void read_userfile();					//получить список учителей или студентов из файла
	bool add_user(const string & type);		//зарегистрировать и добавить в set нового пользователя
	void update_user();						//сохранить данные о пользователях в файл
	void print_users(ostream& sout);  		//вывести список студентов, сдавших тест, или препод., кот. редактировали тесты
	void set_grade(Test & t);				//выставить оценку и занести в сет 
	
	//методы только для преподов
	bool sign_in();
	void delete_user();
	
private:
	set<UserT*> Users; 			//упорядоченный список студентов (имя/группа/оценка) или преподавателей (имя/пароль)
	Student* current_student;	//вошедший студент, до окончания теста помещаем его сюда, после -- в сет
	fstream userdata;
	string filename;

	Manager(const Manager& manager);
	Manager& operator=(const Manager& manager);
};

//для поиска по имени
class find_by_name
{
public:
	find_by_name(UserT * compare_to) : compare_to_(compare_to) {}
	bool operator()(UserT *user)
	{
		if (strcmp(user->name(), compare_to_->name()) == 0)
			return true;
		else
			return false;
	}
private:
	UserT * compare_to_;
};

#endif