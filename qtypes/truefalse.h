#ifndef TRUE_FALSE_H
#define TRUE_FALSE_H
#include <fstream>
#include <iostream>
#include "../question.h"
using namespace std;

class TrueFalse : public Question 
{
	/*унаследованные
	char question_[80]; 		//текст вопроса
	char answer_[20];			//текст ответа*/
protected:
	virtual void print(ostream& sout) const 
	{
	   sout << "Question: True/False\n" << question_ << endl;
	}
	
public:
	TrueFalse(string q = "", string ans = "") : Question(q, ans, "Question: True/False") {}
	
	virtual void print_answer(ostream& sout) const
	{
		sout << answer_ << endl;
	}

	//функции для записи/чт в dat-файл
	virtual void save(fstream& of)
	{
		of.write(type(), 80);
		of.write(question_, sizeof(question_));
		of.write(answer_, sizeof(answer_));
	}
	virtual void load(fstream& inf)
	{
		inf.read(question_, sizeof(question_));
		inf.read(answer_, sizeof(answer_));
	}
};

#endif