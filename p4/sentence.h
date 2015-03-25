#ifndef SENT_H
#define SENT_H
#include <iostream>
#include <string>
#include "element.h"
using namespace std;

class Sentence : public Element
{
	public:

		Sentence(string input);
	
		virtual void complete(const Dict &d);
	
		virtual void check(const Dict &d);
	
		virtual void show() const;
	
	private:
		
		string key;
		string dSentence;
		string print[10];



	};




#endif
