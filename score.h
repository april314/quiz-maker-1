#ifndef SCORE_H
#define SCORE_H
#include <iostream>
using namespace std;

class Score
{

public:
	Score(int m) : score_(0), max_(m) {}

	int score() { return score_; }

	void reset()
	{
		score_ = 0;
		max_ = 0;
	}

	void increment_max()
	{
		max_++;
	}

	friend Score& operator++(Score& s)
	{
		s.score_ += 1;
		return s;
	}

	friend ostream& operator<<(ostream& sout, Score& s)
	{
		int result = static_cast<int>(((double)s.score_ / (double)s.max_) * 100);
		sout << s.score_ << "/" << s.max_ << " (" << result << "%)";
		s.score_ = static_cast<int>(result / 100);
		sout << "Your grade is: " << s.score_ << endl;
		return sout;
	}

private:
	int score_;
	int max_;
};

#endif