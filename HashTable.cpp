#include "HashTable.h"

HashTable::HashTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table[i] = nullptr;
        state[i] = 0;
    }
    itemCount = 0;
    collisionCount = 0;
    longestProbe = 0;
}

int HashTable::hashFunction(const string& callsign) {       //converts callsign string to array index
    int sum = 0;
    for (unsigned i = 0; i < callsign.size(); i++)
        sum = (sum * 31 + callsign[i]) % HASH_TABLE_SIZE;
    return sum;
}

void HashTable::insert(const string& callsign, Flight* flight) {
    if (itemCount >= HASH_TABLE_SIZE) return;
    int index = hashFunction(callsign);
    int probes = 0;
    while (state[index] == 1) {
        collisionCount++;
        probes++;
        index = (index + 1) % HASH_TABLE_SIZE;
    }

  //stores flight pointer and marks slots as occupied
    table[index] = flight;
    state[index] = 1;
    itemCount++;
    if (probes > longestProbe) longestProbe = probes;
}

Flight* HashTable::find(const string& callsign) {
    int index = hashFunction(callsign);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (state[index] == 0) return nullptr;
        if (state[index] == 1 && table[index]->callsign == callsign) return table[index];
        index = (index + 1) % HASH_TABLE_SIZE;
    }
    return nullptr;
}

bool HashTable::remove(const string& callsign) {
    int index = hashFunction(callsign);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (state[index] == 0) return false;
        if (state[index] == 1 && table[index]->callsign == callsign) {
            state[index] = 2;
            table[index] = nullptr;
            itemCount--;
            return true;
        }
        index = (index + 1) % HASH_TABLE_SIZE;
    }
    return false;
}

void HashTable::displayStats() {
    cout << "Hash table: " << itemCount << "/" << HASH_TABLE_SIZE << " used, load factor "
         << (double)itemCount / HASH_TABLE_SIZE << ", collisions " << collisionCount
         << ", longest probe " << longestProbe << "\n";
}
