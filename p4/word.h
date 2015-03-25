#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <string>
#include "element.h"

using namespace std;

class Word : public Element
{
	public:

		Word(string input);
	
		virtual void complete(const Dict &d);
	
		virtual void check(const Dict &d);
	
		virtual void show() const;
	
	private:
		
		string key;
		string dWord;
		string print[10];



};




#endif
