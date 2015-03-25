#include <vector>
#include <string>
#ifndef DICT_H
#define DICT_H

using namespace std;
class Dict
{

	public:
	
		Dict(string f);			

		~Dict();

		int getLength(int) const;
		
		string getWord(int) const;
		
		string getSent(int) const;
		
		string getPhrase(int) const;
		
	private:
		vector<string> word;
	
		vector<string> phrase;
	
		vector<string> sentences;
	
		int sentSize;
	
		int wordSize;
	
		int phraseSize;
		
};
#endif
