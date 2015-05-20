#include <iostream>
#include "hash.h"

hashTable::hashTable(int size){
	capacity = getPrime(size);
	filled = 0;
	data.assign(capacity, hashItem());
}

int hashTable::insert(const std::string &key, void *pv){
	if(filled > capacity/2){
		if(!rehash()){
			std::cout<< "Too many elements. Hash Table overlaod." <<std::endl;
			return -1;
		}
	}

	hashItem *itemToInsert;
	itemToInsert->key = key;
	itemToInsert->isOccupied = true;
	itemToInsert->isDeleted = false;
	itemToInsert->pv = pv;
	int position = findPos(key);

	if(position == -1){
		if(!rehash()){
			std::cout<< "Too many elements. Hash Table overlaod." <<std::endl;
			return -1;
		}
	}else{
		data.at(position) = *itemToInsert;
		filled++;
		return 0;
	}
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const std::string &key){
	if(findPos(key) == -1) return false;
	return true;
}

void *hashTable::getPointer(const std::string &key, bool *b){ }
int hashTable::setPointer(const std::string &key, void *pv){ return -1; }
bool hashTable::remove(const std::string &key){ return false; }

// The hash function.
int hashTable::hash(const std::string &key){
	int hashVal = 0;
	for(int i = 0; i < key.size(); i++){
		hashVal = 37 * hashVal + key.at(i);
	}
	if(hashVal<0){
		hashVal += capacity;
	}
	return hashVal % capacity;
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const std::string &key){
	if(filled == 0) return -1;
	int position = hash(key);
	int startIndex = position;
	while(data.at(position).isOccupied){
		if(data.at(position).key.compare(key) == 0){
			return position;
		} else {
			position++;
		}
		if(position == capacity) position = 0;
		if(position == startIndex) return -1;
	}
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
	capacity = getPrime(capacity+1);
	if(capacity == -1) return false;
	std::vector<hashItem> tmp = data;
	data.resize(capacity,hashItem());
	for(std::vector::iterator it = tmp.begin(); it!=tmp.end(); it++){
		insert();
	}
}

unsigned int hashTable::getPrime(int size){
	static unsigned int primeList [] = { 50021, 100003, 200003, 500009, 1000003, 2000003};
	for(int i = 0; i < sizeof(primeList); i++){
		if(primeList[i] > size){
			return primeList[i];
		}
	}
	return -1; //no appropriate prime found
}

int main(){

}
