#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Common.h"

class HashTable {
private:
    Flight* table[HASH_TABLE_SIZE];   // stores flight pointers
    int     state[HASH_TABLE_SIZE];   // 0=empty, 1=occupied, 2=tombstone
    int     itemCount;
    int     collisionCount;
    int     longestProbe;

    int hashFunction(const string& callsign);   

public:
    HashTable();
    void    insert(const string& callsign, Flight* flight);
    Flight* find(const string& callsign);      
    bool    remove(const string& callsign);     
    void    displayStats();                     
};

#endif
