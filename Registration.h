#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "Common.h"
#include "HashTable.h"
class Registration {
private:
    Flight*   flightHead;
    Flight*   flightTail;
    Crew*     crewHead;
    Crew*     crewTail;
    int       flightCount;
    HashTable hashTable;

public:
    Registration();
    ~Registration();

    void    addFlight(Flight* flight);
    bool    removeFlight(const string& callsign);
    void    updateAllFlights();
    void    displayAllFlights();
 void    addCrew(Crew* crew);
    void    displayAllCrew();
    Flight* findFlight(const string& callsign);
    string  getPilotName(const string& callsign);
    Flight* getHead();
    int     getFlightCount();
    HashTable& getHashTable();
};

#endif
