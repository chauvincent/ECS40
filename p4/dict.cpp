#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "dict.h"

using namespace std;

Dict::Dict(string f)
{
	ifstream data(f.c_str());
	
	ifstream *fp = &data;
	
	if (!data)
	{
		cerr << "file cannot be opened" << endl;
		
		exit (1);
	}
	
	string buffer;
	
	while(getline(*fp, buffer, '.'))
	{

		
		int nPos = 0, sPos = 0;
		
		sPos = buffer.find(" ");
		
		if (sPos == 0)
		{
			buffer.erase(0,1);
		}
		
		nPos = buffer.find("\n");

		if (nPos > -1)
		{
			buffer.replace(nPos,1," ");
		}
	
		sentences.push_back(buffer.append("."));
		
	}
	for(unsigned int y = 0; y < sentences.size(); y++)
	{
		int nPos = sentences[y].find("\n");
		if (nPos > -1)
		{

			sentences[y].replace(nPos,1," ");
		}
		
	}
		
	fp->clear();
	
	fp->seekg(0);
	
	string wBuffer;
	
	while(getline(*fp, wBuffer, ' '))
	{
		int pPos;
		int nPos;
		int sPos;
		
		sPos = wBuffer.find(" ");
		
		if (sPos > -1)
		{
			
			wBuffer.erase(wBuffer.begin() + sPos);
			
		}
		
		pPos = wBuffer.find(".");
		
		if (pPos > -1)
		{
			wBuffer.erase(wBuffer.begin() + pPos);
		}
		
		nPos = wBuffer.find("\n");
		
		if (nPos > -1)
		{
			wBuffer.replace(nPos,1," ");
		}
		word.push_back(wBuffer);
		
	}
	
	int wSize = word.size();
	
	string buff;
	
	int i = 0;
	
	while(i < wSize-1)   //construct two word phrases
	{
		
		buff.assign(word[i]);
		
		buff.append(" ").append(word[i+1]);
		
		phrase.push_back(buff);
		
		i++;
	}

	buff.clear();

	for(int j = 0; j < wSize-2; j++) //three word
	{
		
		buff.assign(word[j]);
		
		buff.append(" ").append(word[j+1]).append(" ").append(word[j+2]);
		
		phrase.push_back(buff);
	
	
	}
	
	buff.clear();
	
	for(int a = 0; a < wSize-3; a++) //four word
	{
		buff.assign(word[a]);
	
		buff.append(" ").append(word[a+1]).append(" ").append(word[a+2]).append(" ").append(word[a+3]);
		
		phrase.push_back(buff);
	}
	
	buff.clear();
	
	for(int b = 0; b < wSize-4; b++) //five word
	{
		buff.assign(word[b]);
	
		buff.append(" ").append(word[b+1]).append(" ").append(word[b+2]).append(" ").append(word[b+3]).append(" ").append(word[b+4]);
		
		phrase.push_back(buff);
	}
	
	
	sort(word.begin(), word.end());
	
	sort(sentences.begin(), sentences.end());
	
	sort(phrase.begin(), phrase.end());
	
	//filter duplicates
	i = 0;
	
	vector<string>::iterator iw;
	
	iw = unique(word.begin(), word.end());
	
	word.resize(distance(word.begin(), iw));
	
	
	vector<string>::iterator is;
	
	is = unique(sentences.begin(), sentences.end());
	
	sentences.resize(distance(sentences.begin(), is));
	
	
	vector<string>::iterator ip;
	
	ip = unique(phrase.begin(), phrase.end());
	
	phrase.resize(distance(phrase.begin(), ip));
	
	wordSize = word.size();
	
	sentSize = sentences.size();
	
	phraseSize = phrase.size();
	
	
	
}; //end of constructor

int Dict::getLength(int choice) const{
	
	if(choice == 1)
		return wordSize;
	
	if(choice == 2)	
		return sentSize;
	
	if(choice == 3)
		return phraseSize;

	return 0;
	
};

string Dict::getWord(int i) const
{	
	return (word[i]);	
};
		
string Dict::getSent(int i) const
{	
	return (sentences[i]);	
};
		
string Dict::getPhrase(int i) const
{	
	return (phrase[i]);	
};

Dict::~Dict()
{
	
};
