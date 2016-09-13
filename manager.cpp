#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>		//exit(EXIT_FAILURE)
#include <string>
#include <algorithm>		//find_if()

#include "manager.h"
#include "usert.h"
#include "utypes/student.h"
#include "utypes/teacher.h"
using namespace std;

Manager::Manager(const string& usersfile) : filename(usersfile) 
{
	userdata.open("resource/users/" + usersfile + ".dat", ios::in | ios::out | ios::binary);
	if (!userdata)
	{
		cout << "couldn't open user file\n";
		exit(EXIT_FAILURE);
	}

	read_userfile();
}

/*Manager::Manager(const Manager& m) : filename(m.filename)
{
	userdata.open("resource/users/" + filename + ".dat", ios::in | ios::binary);
	if (!userdata)
	{
		cout << "couldn't open user file, creating new one\n";
		exit(EXIT_FAILURE);
	}

	read_userfile();
}*/
	
Manager::~Manager()
{
	userdata.clear();
	userdata.trunc; //empty file

	update_user();
	userdata.close();
	
	for (auto u : Users) 
	{
		delete u;
	}
}

/*Manager& Manager::operator=(const Manager& m)
{
	filename = m.filename;
	userdata.open("resource/users/" + filename + ".dat", ios::in | ios::binary);
	if (!userdata)
	{
		cout << "couldn't open user file\n";
		exit(1);
	}

	read_userfile();
	
	return *this;
}*/

void Manager::read_userfile()
{
	if (!userdata)
	{
		cout << "Couldn't get users./n" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		char keywd[10];

		while (!userdata.fail())
		{
			userdata.read(keywd, sizeof(keywd));
			if (!strcmp(keywd, "Student"))
			{
				Student *s = new Student();
				s->load(userdata);
				Users.insert(s);

				//for debug
				cout << "User *s from file:\n";
				cout << s << endl;
			}
			else if (!strcmp(keywd, "Teacher"))
			{
				Teacher *t = new Teacher();
				t->load(userdata);
				Users.insert(t);

				//for debug
				cout << "\nUser *t from file:\n";
				cout << t << endl;
			}
		}
	}

	//для отладки
	cout << "\nall users in set of *u:\n";
	int i = 1;
	for (auto u : Users)
	{
		cout << i << ". \n" << u << endl;
		++i;
	}
	cout << "There are " << Users.size() << " users in the set of *u\n\n" << endl;
}

bool Manager::add_user(const string & type)
{
	if (type == "Teacher")
	{
		string username;
		string password;
		cout << "Enter your name: \n";
		cin >> username;
		cin.sync();
		cin.clear();
		Teacher *t = new Teacher(username);
		//auto user = Users.find(t); это неправильно для сравнения не по всем полям

		set<UserT*>::iterator user = find_if(Users.begin(), Users.end(), find_by_name(t));
		if (user == Users.end())
		{
			cout << "Enter your password: \n";
			cin >> password;
			t->set_password(password);
			cin.sync();
			cin.clear();

			Users.insert(t);
			cout << "You have successfully registered\n" << endl;

			//for debug
			cout << t << endl;

			return true;
		}
		else
		{
			cout << "Account already exists!\n" << endl;
			cin.get();
			cin.sync();
			cin.clear();
			return false;
		}
	}
	else if (type == "Student")
	{
		string username;
		string group;
		cout << "Enter your name: \n";
		cin >> username;
		cin.sync();
		cin.clear();
		cout << "Enter your group: \n";
		cin >> group;
		Student *s = new Student(username, group);

		//auto user = Users.find(s); это неправильно для сравнения не по всем полям членов сета
		
		set<UserT*>::iterator user = find_if(Users.begin(), Users.end(), find_by_name(s));

		if (user == Users.end())
		{
			current_student = s;
			cout << "You have successfully registered\n" << endl;
			//вставка в сет после прохождения теста
			return true;
		}
		else
		{
			cout << "You have already passed the test!\n" << endl;
			cin.get();
			cin.sync();
			cin.clear();
			return false;
		}
	}
}

//запись в файл
void Manager::update_user()
{
	for (auto u : Users)
	{
		u->save(userdata);
	}
}

//вывод на экран или текстовый файл
void Manager::print_users(ostream& sout)
{
	for (auto u : Users)
	{
		if (strcmp(u->type(), "Student") == 0)
		{
			sout << u << endl;
		}
	}
}

void Manager::set_grade(Test & t)
{
	current_student->set_grade(t.get_score());
	Users.insert(current_student);
}

//только для преподавателей
bool Manager::sign_in()
{
	string nickname, pswrd;
	cout << "Enter your name: \n";
	cin >> nickname;
	cin.sync(); 			//removing any unread character from the standard input queue of characters
	cin.clear();
	cout << "Enter Password: \n";
	cin >> pswrd;
	cin.sync(); 
	cin.clear();
	Teacher * t = new Teacher(nickname, pswrd);

	// Check if the account resides in Users
	//auto user = Users.find(t);
	set<UserT*>::iterator user = find_if(Users.begin(), Users.end(), find_by_name(t));
	if (user == Users.end())
	{
		cout << "No such account!\n";
		return false;
	}	
	else
	{
		cout << "You are logged in\n";
		return true; // True = Account found | False = Account not found
	}
}

void Manager::delete_user()
{
	string username, group;
	cout << "Enter the name: \n";
	cin >> username;
	cin.sync(); 			//removing any unread character from the standard input queue of characters
	cin.clear();
	cout << "Enter the group: \n";
	cin >> group;
	cin.sync();
	cin.clear();
	Student * s = new Student(username, group);
	//auto user = Users.find(s);
	set<UserT*>::iterator user = find_if(Users.begin(), Users.end(), find_by_name(s));
	if (user != Users.end())
	{
		Users.erase(user);
		cout << "Account deleted.\n" << endl;
		cin.sync(); 
		cin.clear();
	}
	else
	{
		cout << "Account does not exist.\n" << endl;
		cin.sync();
		cin.clear();
	}
}