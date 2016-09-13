#define _CRT_SECURE_NO_WARNINGS
//главный файл программы
#include <iostream>
#include <string>
#include <ctime>
#include "usert.h"
#include "utypes/teacher.h"
#include "utypes/student.h"
#include "tests.h"
#include "manager.h"
using namespace std;

//главное меню
int main_menu();
//меню для студентов
int menu_students();
//меню для преподавателей
int menu_teachers();
int menu_teacher_2();

int main(int argc, char** argv)
{
	srand(time(0));
	Manager *m = new Manager();
	Test *t = new Test(rand());
	
	int main_menu_result = main_menu();
	
	switch(main_menu_result)
	{
		//хотим зайти как студент.
		case 1:
		{
			int menu_students_result = menu_students();
			//зарегистрироваться и пройти тест
			if (menu_students_result == 1)
			{
				if(m->add_user("Student"))
				{
					t->start();
					t->end();
					m->set_grade(*t);
					m->update_user();
				}
			}
			break;
		}
		//хотим зайти как препод.
		case 2:
		{
			int menu_teachers_result = menu_teachers();
			bool ok;
			//войти
			if (menu_teachers_result == 1)
			{
				ok = m->sign_in();
			}
			//регистрация
			else if (menu_teachers_result == 2)
			{
				ok = m->add_user("Teacher");
			}
			if (ok)
			{
				int menu_teach_2;
				while ((menu_teach_2 = menu_teacher_2()) != 7)
				{
					switch(menu_teach_2)
					{
						//вывести список студентов
						case 1:
						{	
							m->print_users(cout);
						break;
						}
						//удалить пользователя
						case 2:
						{	
							m->delete_user();
						break;
						}
						//добавить вопрос
						case 3:
						{	
							t->add_question();
						break;
						}
						//удалить вопрос
						case 4:
						{	
							int num = 0;
							cout << "Enter the number: ";
							cin >> num;
							t->delete_question(num);
						break;
						}
						//редактировать вопрос
						case 5:
						{	
							int num = 0;
							cout << "Enter the number: ";
							cin >> num;
							t->edit_question(num);
						break;
						}
						//удалить все вопросы
						case 6:
						{	
							t->erase_all();
						break;
						}
					}
				}	
			}
			
			break;
		}
	}
	
	delete m;
	delete t;
	
	return 0;
}

//главное меню
int main_menu()
{
	cout << "\nWelcome to Test Wizard! Choose numbers to continue:\n";
	cout << "\n 1. For students\n";
	cout << " 2. For teachers\n";
	cout << " 3. Exit\n";
	int result;
	cout << "Enter: ";
	cin >> result;
	if (result < 1 || result > 3)
	{
		cout << "Wrong selection, please try again. \n";
		return main_menu();
	}
	return result;
}

//меню для студентов
int menu_students()
{
	cout << "\n 1. Sign in and take a test\n";
	cout << " 2. Back to main menu\n";
	int result;
	cout << "Enter: ";
	cin >> result;
	if (result < 1 || result > 2)
	{
		cout << "Wrong selection, please try again. \n";
		return menu_students();
	}
	else if(result == 2)
	{
		return main_menu();
	}
	return result;
}

//меню для преподавателей
int menu_teachers()
{
	cout << "\n 1. Log in\n";
	cout << " 2. Register\n";
	cout << " 3. Back to main menu\n";
	int result;
	cout << "Enter: ";
	cin >> result;
	if (result < 1 || result > 3)
	{
		cout << "Wrong selection, please try again. \n";
		return menu_teachers();
	}
	else if(result == 3)
	{
		return main_menu();
	}
	return result;
}
//после входа
int menu_teacher_2()
{
	cout << "\n 1. View students.\n";
	cout << " 2. Delete user.\n";
	cout << " 3. Add question.\n";
	cout << " 4. Delete question.\n";
	cout << " 5. Edit question.\n";
	cout << " 6. Delete all questions.\n";
	cout << " 7. Exit\n";
	int result;
	cout << "Enter: ";
	cin >> result;
	if (result < 1 || result > 7)
	{
		cout << "Wrong selection, please try again. \n";
		return menu_teachers();
	}
	return result;
}