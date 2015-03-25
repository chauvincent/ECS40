#include "phrase.h"
#include "element.h"
using namespace std;

Phrase::Phrase(string s) : key(s) {}

void Phrase::complete(const Dict &d){

	cout << "Phrase completion for: " << key << endl;

	cout << "--------------------------------" << endl;

	int PhraseSize = d.getLength(3);
	
	int found = 0;

	for(int j = 0; j < PhraseSize; j++){

		int tester = 1;

		string dPhrase = d.getPhrase(j);
	
			for(unsigned int i = 0; i < key.length(); i++)
			{

				if(key[i] != dPhrase[i])
				{
			
					tester = 0;

					break;
				} 		
		
			}

		if (tester == 1)
		{
			cout << dPhrase << endl;
			
			found = 1;
		}		
	
	}
	
	if(found != 1)
		cout << "no completion found " << endl << " " << endl; 
}
	
void Phrase::check(const Dict &d){
	
	int PhraseSize = d.getLength(3); 

	string closePhrases[PhraseSize];

	int distanceVector[PhraseSize];


	cout << endl << "Phrase correction for: " << key << endl;

	cout << "--------------------------------" << endl;

	for(int k = 0; k < PhraseSize; k++)
	{
		
		dPhrase = d.getPhrase(k);

		int greater = 0;

		int dLength = dPhrase.length();
		
		int kLength = key.length()-1;

		if(dLength>kLength){
		
			greater = dLength;
		
		}
		else{

			greater = kLength;
		}

		int distance = 0; 

		for(int j = 0; j < greater; j++)
		{
			if(key[j] != dPhrase[j]){
				distance++;		
			}

		}

		if(k < 10)
		{
			distanceVector[k] = distance;
			closePhrases[k] = dPhrase;
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
					
						closePhrases[y] = closePhrases[y-1];
					}
				
					distanceVector[z] = distance;

					closePhrases[z] = dPhrase;

					break;
				}
			}
		}

	} //end outer for

	for(int u = 0; u < 10; u++)
		print[u].assign(closePhrases[u]); 
	
} //end check
	
void Phrase::show() const
{
	
	for(int i = 0; i < 10; i++)
		cout << print[i] << endl;	
	 
}
