#ifndef QUESTION_H
#define QUESTION_H
#include <iostream>
#include <string>
using namespace std;

class Question
{
private:
	char type_[80];				//TF, MC, OP

protected:
	virtual void print(ostream& sout) const = 0;
	
	char question_[180]; 		//текст вопроса
	char answer_[20];			//текст ответа*/
public:
	Question(string q, string ans, string t)
	{ 
		strcpy(question_, q.c_str()); 
		strcpy(answer_, ans.c_str());
		strcpy(type_, t.c_str());
	}

	virtual ~Question() {}
	// аксессоры
	char* question(){ return question_; }
	char* answer() 	{ return answer_; }
	char* type() 	{ return type_; }
	// виртуальные аксессоры (для MC)
	virtual char* a() const { return ""; }
	virtual char* b() const { return ""; }
	virtual char* c() const { return ""; }
	virtual char* d() const { return ""; }

	virtual void print_answer(ostream& sout) const = 0;

	friend ostream& operator<<(ostream& sout, Question* &q) 
	{
		q->print(sout);
		return sout;
	}
	//Для работы с файлами dat
	virtual void save(fstream & of) = 0;
	virtual void load(fstream & inf) = 0;
};

#endif