#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>


using namespace std;
//Inputs
int main(){
	string dictionaryFileName;
	cout << "Enter name of dictionary file: ";
	cin >> dictionaryFileName;

	clock_t t1, t2;
	t1 = clock();

	string fileString = "";

	ifstream input(dictionaryFileName.c_str());
	if (!input) {
		cerr << "Error: could not open " << dictionaryFileName << endl;
		exit(1);
	}

	// The first line indicates the size
	string line;
	while ( getline (input,line) )
    {
    	fileString = line;
    }
	// Load the data
	input.close();
	t2 = clock();
	cout<< fileString << endl;
	cout<< "Time elapsed to open the dictionary: " << t2-t1 << " seconds." << endl;

	string documentSpellCheckName;
	cout << "Enter name of document file to be spell checked: ";
	cin >> documentSpellCheckName;
	
	string outputFileName;
	cout << "Enter the name of output file: ";
	cin >> outputFileName;

}
