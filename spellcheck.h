#ifndef _CHECK_H
#define _CHECK_H

#include <iostream>
#include <fstream>
#include <vector>
#include "hash.h"

class dictionary{

public:
	//Constructor
	dictionary(){};
	//Function that reads in the dictionary
	void loadDictionary(const std::string &dictionaryFileName);
	//Function that reads in the file to be spellchecked
	void readFile(const std::string fileToCheckName, const std::string outFileName);

private:
	//HashTable that stores the dictionary
	hashTable *h = new hashTable();
	//Function that converts all strings into lower case
	std::string toLowerCase(std::string word);
	//Functions to tokenize strings
	std::vector<std::string> split(const std::string &s, char delim);
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
	//boolean to get rid of all invalid words
	bool isValidWord(const char c);
};

#endif //_CHECK_H