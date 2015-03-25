#include "sentence.h"
#include "element.h"
using namespace std;
Sentence::Sentence(string s) : key(s) {}

void Sentence::complete(const Dict &d){

	cout << "Sentence completion for: " << key << endl;

	cout << "--------------------------------" << endl;

	int sSize = d.getLength(2);
	
	int found = 0;

	for(int j = 0; j < sSize; j++)
	{
		int tester = 1;

		string dSentence = d.getSent(j);
	
			for(unsigned int i = 0; i < key.length(); i++)
		
				if(key[i] != dSentence[i])
				{
					tester = 0;
					break;
				} 		
				
		if (tester == 1)
		{
			cout << dSentence << endl;
			found = 1;
		}		
	
	}
	if(found != 1)
		cout << "no completion found " << endl << " " << endl; 
	
}
	
void Sentence::check(const Dict &d)
{
	
	int sSize = d.getLength(2); 

	string closeSents[sSize];

	int distanceVector[sSize];

	cout << endl << "SENTENCE correction for: " << key << endl;

	cout << "--------------------------------" << endl;

	for(int k = 0; k < sSize; k++)
	{
		
		dSentence = d.getSent(k);

		int greater = 0;

		int dLength = dSentence.length();
		
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
		
			if(key[j] != dSentence[j])

				distance++;		

		if(k < 10)
		{
			distanceVector[k] = distance;
			closeSents[k] = dSentence;
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
					
						closeSents[y] = closeSents[y-1];
					}
				
					distanceVector[z] = distance;

					closeSents[z] = dSentence;

					break;
				}
			}
		}

	} //end outer for

	for(int u = 0; u < 10; u++)
		print[u].assign(closeSents[u]); 

} //end check
	
void Sentence::show() const
{	
	for(int i = 0; i < 10; i++)
		cout << print[i] << endl;	
}
