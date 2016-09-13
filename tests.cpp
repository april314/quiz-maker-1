#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>   //transform, random_shuffle
#include <cstdlib>
#include <fstream>
#include <cstdlib>

#include "tests.h"
#include "score.h"
#include "question.h"
#include "qtypes/multchoice.h"
#include "qtypes/truefalse.h"
#include "qtypes/open.h"

using namespace std;

Test::Test(int seed, string file) : name_(file), seed_(seed), score_(0) 
{
	file_.open("resource/questions/" + file + ".dat", ios::in | ios::out | ios::binary);
	if (!file_)
	{
		std::cout << "Cannot open test file, creating new one\n";
		exit(EXIT_FAILURE);
	}

	get_questions();
}

Test::~Test()
{
	file_.clear();
	file_.trunc; //empty file

	update_test();
	file_.close();

	for (auto q : questions_)
	{
		delete q;
	}
}

/*Test& Test::operator=(const Test& test)
{
	name_ = test.name_;
	fstream file_("resource/questions/" + name_ + ".dat", ios::in | ios::binary);
	if (!file_)
	{
		cout << "Cannot open test file, creating new one\n";
		exit(EXIT_FAILURE);
	}

	return *this;
}*/

// Random number generator
int myrandom(int i) { return rand() % i; }

void Test::get_questions()
{
	srand(seed_);
	if (!file_)
	{
		std::cout << "Couldn't get questions.\n" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		char keyword[80];

		while (!file_.fail())
		{
			file_.read(keyword, sizeof(keyword));

			if (!strcmp(keyword, "Question: Multiple Choice"))
			{
				MultipleChoice * q = new MultipleChoice();
				q->load(file_);
				questions_.push_back(q);
			}
			else if (!strcmp(keyword, "Question: True/False"))
			{
				TrueFalse * q = new TrueFalse();
				q->load(file_);
				questions_.push_back(q);
			}
			else if (!strcmp(keyword, "Question: Open"))
			{
				OpenQuestion * q = new OpenQuestion();
				q->load(file_);
				questions_.push_back(q);
			}
			score_.increment_max();		//увеличиваем макс баллы (по 1 за каждый вопрос)
		}
	}
	std::random_shuffle(questions_.begin(), questions_.end(), myrandom);

	//для отладки
	std::cout << "for debugging\n";
	for (auto q : questions_)
	{
		int i = 1;
		std::cout << i << q << endl;
		++i;
	}
	std::cout << "Max score is " << score_.score() << endl; 
}

// Start the Test
void Test::start()
{
	for (auto q : questions_)
	{
		ask_question(q);
	}
	end();
}

// Ask the next quesiton in sequence
void Test::ask_question(Question* & q)
{
	string ans;

	cout << "Type EXIT to quit\n\n";
	std::cout << q;
	cin >> ans;
	transform(ans.begin(), ans.end(), ans.begin(), ::toupper);

	if (ans == "EXIT")
	{
		std::cout << endl;
		end();
	}
	else
	{
		if (ans == q->answer())
		{
			std::cout << "Correct Answer!" << endl;
			++score_;
		}
		else
		{
			std::cout << "Incorrect, the answer was: " << q->answer() << "." << endl;
		}
		std::cout << endl;
	}
}

void Test::end()
{
	std::cout << "Your score is: " << score_ << "." << endl;
}

void Test::update_test()
{
	for (auto q : questions_)
	{
		q->save(file_);
	}
}

void Test::add_question()
{
	string type, question, answer;
	std::cout << "Enter type (MC, OP or TF): ";
	cin >> type;
	cin.sync();
	cin.clear();
	cout << "Enter a question:\n";
	getline(cin, question);
	transform(type.begin(), type.end(), type.begin(), ::toupper);
	if (type == "MC")
	{
		string a, b, c, d;
		std::cout << "Enter A) ";
		getline(cin, a);
		std::cout << "Enter B) ";
		getline(cin, b);
		std::cout << "Enter C) ";
		getline(cin, c);
		std::cout << "Enter D) ";
		getline(cin, d);
		std::cout << "Enter correct answer: ";
		getline(cin, answer);

		MultipleChoice * q = new MultipleChoice(question, a, b, c, d, answer);
		questions_.push_back(q);
	}
	else if (type == "TF")
	{
		cout << "Enter a correct answer:\n";
		getline(cin, answer);
		TrueFalse * q = new TrueFalse(question, answer);
		questions_.push_back(q);
	}
	else if (type == "OP")
	{
		cout << "Enter a correct answer:\n";
		getline(cin, answer);
		OpenQuestion * q = new OpenQuestion(question, answer);
		questions_.push_back(q);
	}
	score_.increment_max();		//увеличиваем макс баллы (по 1 за каждый вопрос)
}

void Test::edit_question(int & n)
{
	if ((!questions_.empty()) && (n > 0) && (n <= questions_.size()))
	{
		std::cout << "Question for editing is:\n" << questions_.at(n) << endl;
		questions_.erase(questions_.begin() + n);
		std::cout << "Old one is deleted.\n";
		add_question();
	}
}

void Test::delete_question(int & n)
{
	if (!questions_.empty() && n > 0 && n <= questions_.size())
	{
		std::cout << "Question for deleting is:\n" << questions_.at(n) << endl;
		questions_.erase(questions_.begin() + n);
		std::cout << "Deleted.\n";
	}
}

void Test::erase_all()
{
	questions_.clear();
}