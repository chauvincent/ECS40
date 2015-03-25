#include "word.h"
#include "element.h"
using namespace std;

Word::Word(string s) : key(s) {}

void Word::complete(const Dict &d){

	cout << "Word completion for: " << key << endl;

	cout << "--------------------------------" << endl;

	int wordSize = d.getLength(1);
	
	int found = 0;

	for(int j = 0; j < wordSize; j++)
	{
		int tester = 1;

		string dWord = d.getWord(j);
	
			for(unsigned int i = 0; i < key.length(); i++)
			{

				if(key[i] != dWord[i])
				{
			
					tester = 0;

					break;
				} 		
		
			}

		if (tester == 1)
		{
			cout << dWord << endl;

			found = 1;
		}		
	
	}
	
	if(found != 1)
		cout << "no completion found " << endl << " " << endl; 
	
}
	
void Word::check(const Dict &d){
	
	int wordSize = d.getLength(1); 

	string closeWords[wordSize];

	int distanceVector[wordSize];

	cout << endl << "WORD correction for: " << key << endl;

	cout << "--------------------------------" << endl;

	for(int k = 0; k < wordSize; k++)
	{
		
		dWord = d.getWord(k);

		int greater = 0;

		int dLength = dWord.length();
		
		int kLength = key.length()-1;

		if(dLength>kLength)
		{
			greater = dLength;
		}
		else
		{
			greater = kLength;
		}

		int distance = 0; 

		for(int j = 0; j < greater; j++)
		{
			if(key[j] != dWord[j])
				distance++;		

		}

		if(k < 10)
		{
			distanceVector[k] = distance;
			closeWords[k] = dWord;
		}
		else
		{
			for(int z = 0; z<10; z++)
			{
				if(distance < distanceVector[z])
				{
					for(int y = 11; y > z; y--)
					{
						distanceVector[y] = distanceVector[y-1];
					
						closeWords[y] = closeWords[y-1];
					}
				
					distanceVector[z] = distance;

					closeWords[z] = dWord;

					break;
				}
			}
		}

	} //end outer for

	for(int u = 0; u < 10; u++)
		print[u].assign(closeWords[u]); 
	
} //end check
	
void Word::show() const{
	
	for(int i = 0; i < 10; i++)
		cout << print[i] << endl;
	
	
}
