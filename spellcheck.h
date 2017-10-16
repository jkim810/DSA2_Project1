#ifndef _CHECK_H
#define _CHECK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <set>
#include "hash.h"

using namespace std;

class dictionary{

public:
	//Constructor
	dictionary(){};
	//Function that reads in the dictionary
	void loadDictionary(const string &dictionaryFileName);
	//Function that reads in the file to be spellchecked
	void readFile(const string fileToCheckName, const string outFileName);

private:
	//HashTable that stores the dictionary
	hashTable *h = new hashTable();
	//Function that converts all strings into lower case
	string toLowerCase(const string &word);
	//boolean to get rid of all invalid words
	bool isValidWord(const char c);
	bool hasDigits(const string& word);
};

#endif //_CHECK_H
