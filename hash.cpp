#include "hash.h"

using namespace std;

hashTable::hashTable(int size){

	capacity = getPrime(size);
	filled = 0;
	data.assign(capacity, hashItem("",false,false,NULL));
}

int hashTable::insert(const string &key, void *pv){
	//rehash if half of the table is filled
	if(capacity == 0 || filled > capacity/2){
		if(rehash() == false){
			return 2;
		}
	}

	//return 1 if key exists
	if(contains(key)) return 1;

	//otherwise insert
	hashItem *itemToInsert = new hashItem(key, true, false, NULL);
	int position = hash(key);

	//linear probing
	while(data.at(position).isOccupied){
		position++;
		if(position == capacity) position = 0;
	}

	data.at(position) = *itemToInsert;
	filled++;
	return 0;
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const string &key){
	if(findPos(key) == -1) return false;
	return true;
}

hashTable::hashItem::hashItem(const string &key, bool isOccupied, bool isDeleted, void *pv)
    :key(key), isOccupied(isOccupied), isDeleted(isDeleted), pv(pv) { }

//void *hashTable::getPointer(const string &key, bool *b){ }
int hashTable::setPointer(const string &key, void *pv){ return -1;}

bool hashTable::remove(const string &key){ return false; }

int hashTable::hash(const string &key){
	unsigned int hash = 5381;
	for(int i = 0; i < key.length(); i++)  hash = ((hash << 5) + hash) + key.at(i); 
	hash = hash%capacity;
    return (int) hash;
}

int hashTable::findPos(const string &key){
	int position = hash(key);
	while(data.at(position).isOccupied == true){
		if(data.at(position).key.compare(key) == 0){
			return position;
		}
		position++;
		if(position == capacity) position = 0;
	}
	return -1;
}

bool hashTable::rehash(){
	capacity = getPrime(filled);
	if(capacity == 0){
		cout<< "Error: Rehash Failed. Data set too big." <<endl;
		return false;
	}
	vector<hashItem> tmp = data;
	data.assign(capacity,hashItem("",false,false,NULL));
	filled = 0;
	for(vector<hashItem>::iterator it = tmp.begin(); it!=tmp.end(); it++){
		if(it->isOccupied) insert(it->key);
	}
	return true;
}

unsigned int hashTable::getPrime(int size){
	static unsigned int primeList[] = {50021, 100003, 200003, 500009, 1000003, 2000003, 4000037 };
	for(int i = 0; i < 6; i++){
		if(primeList[i]/2 > size){
			return primeList[i];
		}
	}
	return 0; //no appropriate prime found
}
