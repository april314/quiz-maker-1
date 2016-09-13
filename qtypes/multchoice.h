//множественный выбор, 4 варианта
#ifndef MULT_CHOICE_H
#define MULT_CHOICE_H
#include <fstream>
#include <iostream>
#include <string>
#include "../question.h"
using namespace std;

class MultipleChoice : public Question 
{
private:
	char a_[10];
	char b_[10];
	char c_[10];
	char d_[10];
	/*унаследованные
	char question_[80]; 		//текст вопроса
	char answer_[20];			//текст ответа*/
protected:
	virtual void print (ostream& sout) const 
	{
		sout << "Question: MultipleChoice\n" << question_ << endl;
		sout << a_ << endl << b_ << endl;
		sout << c_ << endl << d_ << endl;
	}
	
public:
	MultipleChoice(string q = "", string a = "", string b = "", string c = "", string d = "", string ans = "")
	: Question(q, ans, "Question: MultipleChoice") 
	{
		strcpy(a_, a.c_str());
		strcpy(b_, b.c_str());
		strcpy(c_, c.c_str());
		strcpy(d_, d.c_str());
	}

	// аксессоры
	virtual char* a() { return a_; }
	virtual char* b() { return b_; }
	virtual char* c() { return c_; }
	virtual char* d() { return d_; }
	
	void print_answer(ostream& sout) const
	{
		sout << answer_ << endl;
	}

	//функции для записи/чт в dat-файл
	virtual void save(fstream& of)
	{
		of.write(type(), 80);
		of.write(question_, sizeof(question_));
		of.write(a_, sizeof(a_));
		of.write(b_, sizeof(b_));
		of.write(c_, sizeof(c_));
		of.write(d_, sizeof(d_));
		of.write(answer_, sizeof(answer_));
	}
	virtual void load(fstream& inf)
	{
		inf.read(question_, sizeof(question_));
		inf.read(a_, sizeof(a_));
		inf.read(b_, sizeof(b_));
		inf.read(c_, sizeof(c_));
		inf.read(d_, sizeof(d_));
		inf.read(answer_, sizeof(answer_));
	}
};

#endif