#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <ctime>
#include "hash.h"
#include "spellcheck.h"

void dictionary::loadDictionary(const std::string &dictionaryFileName){

	std::ifstream input(dictionaryFileName.c_str());
	if(!input){
		std::cerr<<"Error: File could not open." << std::endl;
		exit(0);
	}

	while(!input.eof()){
		std::string line;
		std::getline(input, line);
		if(line == "") break;
		line = toLowerCase(line);
		h->insert(line);
	}
	
	input.close();	
}

void dictionary::readFile(const std::string fileToCheckName, const std::string outFileName){
	
	std::ifstream input(fileToCheckName.c_str());
	if(!input){
		std::cerr<<"Error: File could not open." << std::endl;
		exit(0);
	}

	std::ofstream output(outFileName.c_str());
	if (!output) {
   		std::cerr << "Error: could not open " << outFileName << std::endl;
   		exit(1);
  	}
	
	int index, counter, lineCounter;

	lineCounter = 0;

	while(!input.eof()){

		lineCounter++;

		//Variables
		std::string line, word;
		std::string::iterator it;
		std::getline(input, line);
		counter = 0;

		//output << "Original Line: " << line << std::endl;
		line = toLowerCase(line);

		std::vector<std::string> x = split(line, ' ');
		for(std::vector<std::string>::iterator it = x.begin(); it!=x.end(); it++){
			std::string tmp = (*it);
			if(tmp.length() > 20){
		    	output << "Long word at line " << lineCounter << ", starts: " << tmp.substr(0,20) << std::endl;
		    }else if(!h->contains(tmp)){
		    	output << "Unknown word at line " << lineCounter << ": " << tmp << std::endl;
		    }
		}	
	}

	input.close();
	output.close();
}

std::string dictionary::toLowerCase(std::string word){

	std::string tmp = "";

	std::string::iterator it;
	for(it = word.begin(); it != word.end(); it++){
		char c = (*it);
		if(c > 64 && c < 91){
			c = c + 32;
		}
		if(isValidWord(c)){
			tmp.push_back(c);
		}
	}

	return tmp;
}

bool dictionary::isValidWord(const char c){
	if((c > 64 && c < 91) || (c > 47 && c < 58) ||c == 45 || c == 92 || c == 32 || c == 39 ||(c > 96 && c < 123)){
		return true;
	}
	return false;
}

std::vector<std::string> &dictionary::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> dictionary::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main(){
	dictionary *dic = new dictionary();
	std::string dictionaryFileName, documentSpellCheckName, outputFileName;
	clock_t t1, t2;
	double timeDiff;

	std::cout << "Enter name of dictionary: ";
	std::cin >> dictionaryFileName;

	t1 = clock();
	dic -> loadDictionary(dictionaryFileName);
	t2 = clock();
	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	std::cout<< "Total time (in seconds) to load dictionary: " << timeDiff << std::endl;

	std::cout << "Enter name of input file: ";
	std::cin >> documentSpellCheckName;
	std::cout << "Enter name of output file: ";
	std::cin >> outputFileName;

	t1 = clock();
	dic -> readFile(documentSpellCheckName, outputFileName);
	t2 = clock();
	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	std::cout<< "Total time (in seconds) to check document: " << timeDiff << std::endl;
}