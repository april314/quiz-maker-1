#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "question.h"
#include "score.h"
using namespace std;

class Test
{
public:
	Test(int seed = 0, string file = "newtest"); 	//конструктор по умолчанию
	~Test();
	
	//методы для прохождения теста
	void get_questions();			//достать вопросы из файла
	void start();
	void ask_question(Question* &q); //ссылка на указатель
	int get_score() { return score_.score(); }
	void end();
	
	void update_test();
	
	//методы для редактирования тестов
	void add_question();
	void delete_question(int & n);
	void edit_question(int & n);
	void erase_all();
	
private:
	int seed_;			//для генератора случ чисел
	string name_;
	fstream file_;		//для считывания теста и для создания нового теста
	Score score_;		//макс балл
	vector<Question*> questions_;

	Test(const Test& a_test);
	Test& operator=(const Test& test);

};

#endif //!TESTS_H