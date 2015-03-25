#ifndef PHRASE_H
#define PHRASE_H
#include <iostream>
#include <string>
#include "element.h"

using namespace std;

class Phrase : Element
{
	public:

		Phrase(string input);
	
		virtual void complete(const Dict &d);
	
		virtual void check(const Dict &d);
	
		virtual void show() const;
	
	private:
		
		string key;
		string dPhrase;
		string print[10];



	};




#endif
