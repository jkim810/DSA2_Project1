#include <iostream>
#include <string>
#include "hash.h"

hashTable::hashTable(int size){

	capacity = getPrime(size);
	filled = 0;
	data.assign(capacity, hashItem("",false,false,NULL));
}

int hashTable::insert(const std::string &key, void *pv){

	if(capacity == 0 || filled > capacity/2){
		if(rehash() == false){
			return 2;
		}
	}

	if(contains(key)){
		std::cerr<< "Error: Key exists" <<std::endl;
		return 1;
	}

	hashItem *itemToInsert = new hashItem(key, true, false, NULL);
	int position = hash(key);

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
bool hashTable::contains(const std::string &key){
	if(findPos(key) == -1) return false;
	return true;
}

hashTable::hashItem::hashItem(const std::string &key, bool isOccupied, bool isDeleted, void *pv)
    :key(key), isOccupied(isOccupied), isDeleted(isDeleted), pv(pv) { }

//void *hashTable::getPointer(const std::string &key, bool *b){ }
int hashTable::setPointer(const std::string &key, void *pv){ return -1; }
bool hashTable::remove(const std::string &key){ return false; }

int hashTable::hash(const std::string &key){
	int hashVal = 0;
	for(int i = 0; i < key.size(); i++){
		hashVal = 37 * hashVal + key.at(i);
	}
	int moduloHashVal = hashVal % capacity;
	if(moduloHashVal < 0) moduloHashVal += capacity;
	return moduloHashVal;
}

int hashTable::findPos(const std::string &key){
	int position = hash(key);
	//std::cout<< "position: " << position << std::endl;
	while(data.at(position).isOccupied == true){
		//std::cout<<"error?"<<std::endl;
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
		std::cout<< "Error: Rehash Failed. Data set too big." <<std::endl;
		return false;
	}
	std::vector<hashItem> tmp = data;
	data.assign(capacity,hashItem("",false,false,NULL));
	filled = 0;
	for(std::vector<hashItem>::iterator it = tmp.begin(); it!=tmp.end(); it++){
		if(it->isOccupied) insert(it->key);
	}
	return true;
}

unsigned int hashTable::getPrime(int size){
	static unsigned int primeList[] = {50021, 100003, 200003, 500009, 1000003, 2000003 };
	for(int i = 0; i < 6; i++){
		if(primeList[i]/2 > size){
			return primeList[i];
		}
	}
	return 0; //no appropriate prime found
}