#include "spellcheck.h"

using namespace std;

int main(){
	dictionary *dic = new dictionary();
	string dictionaryFileName, documentSpellCheckName, outputFileName;
	clock_t t1, t2;
	double timeDiff;

	cout << "Enter name of dictionary: ";
	cin >> dictionaryFileName;

	t1 = clock();
	dic -> loadDictionary(dictionaryFileName);
	t2 = clock();
	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout<< "Total time (in seconds) to load dictionary: " << timeDiff << endl;

	cout << "Enter name of input file: ";
	cin >> documentSpellCheckName;
	cout << "Enter name of output file: ";
	cin >> outputFileName;

	t1 = clock();
	dic -> readFile(documentSpellCheckName, outputFileName);
	t2 = clock();
	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout<< "Total time (in seconds) to check document: " << timeDiff <<endl;
}

void dictionary::loadDictionary(const string &dictionaryFileName){
	ifstream input(dictionaryFileName.c_str());
	if(!input){
		cerr<<"Error: File could not open." << endl;
		exit(0);
	}

	while(!input.eof()){

		string line;
		getline(input, line);
		line = toLowerCase(line);
		h->insert(line);
	}

	input.close();	
}

void dictionary::readFile(const string fileToCheckName, const string outFileName){
	
	ifstream input(fileToCheckName.c_str());
	if(!input){
		cerr<<"Error: File could not open." << endl;
		exit(0);
	}

	ofstream output(outFileName.c_str());
	if (!output) {
   		cerr << "Error: could not open " << outFileName << endl;
   		exit(1);
  	}
	
	int lineCtr = 0;

	while(!input.eof()){

		lineCtr++;

		//Parse line by line
		string line;
		getline(input, line);
		line = toLowerCase(line);

		//sets for delimeters since no duplicates should be allowed
		set <char> delim;
		//stores tokenized strings for each line
		vector <string> words;
		
		//tokenize routine
		stringstream ss;
		for(char c: line){
			if(!isValidWord(c))	{
				if(!ss.str().empty()) words.push_back(ss.str());
				ss.str("");
				ss.clear();
				delim.insert(c);
			} else{
				ss << c;
			}
		}
		
		//make sure last word is puhsed into the vector
		if(!ss.str().empty()) words.push_back(ss.str());
		

		for(string tmp: words){
			if(hasDigits(tmp)){
				//ignore words with digits
			}else if(tmp.length() > 20){
			   	//report words longer than 20
			   	output << "Long word at line " << lineCtr << ", starts: " << tmp.substr(0,20) << endl;
			}else if(!h->contains(tmp)){
				//report words not in dictionary
			   	output << "Unknown word at line " << lineCtr << ": " << tmp << endl;
			}
		}	
	}

	input.close();
	output.close();
}

string dictionary::toLowerCase(const string& word){
	stringstream tmp;
	for(char c: word){
		if(c > 64 && c < 91) c += 32;
		tmp << c;
	}
	return tmp.str();
}

bool dictionary::isValidWord(const char c){
	if((c > 64 && c < 91) || (c > 47 && c < 58) || (c == '-') || (c == '\'') ||(c > 96 && c < 123)){
		return true;
	} else {
		return false;
	}
}

bool dictionary::hasDigits(const string& word){
	for(char c: word){
		if(c>= '0' && c<='9'){
			return true;
		}
	}
	return false;
}
