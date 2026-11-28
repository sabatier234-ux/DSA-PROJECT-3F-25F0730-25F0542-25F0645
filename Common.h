// Common.h - shared structs, constants and helpers we all are sharing this file
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;
// status: 0 waiting, 1 landed, 2 crashed, 3 cleared and moving, 4 scheduled, 5 gone
struct Flight {
    string callsign;
    string aircraftType;
    string airline;
    string origin;
    string destination;
    int    passengerCount;
    int    fuelRemaining;
    string currentSector;
    string assignedRunway;
    int    arrivalTick;
    int    priorityLevel;     // 1=War ... 9=Normal
    int    status;
    int    alertTick;         // tick when the emergency started (-1 if none)
    string nextSector;
    int    moveTimer;
    Flight* next;

    Flight() {
        passengerCount = 0; fuelRemaining = 0; arrivalTick = 0;
        priorityLevel = 9; status = 0; alertTick = -1;
        moveTimer = 0; next = nullptr;
    }
};

struct Crew {
    string employeeID;
    string name;
    string role;
    string assignedCallsign;
    Crew*  next;
};
struct Route {
    string sectors[MAX_SECTORS];
    int    pathLength;
    int    totalCost;
    bool   found;
};

struct ScenarioEvent {
    int    tick;
    string eventType;
    string target;
};

struct MissingFlight {
    string flightName;
    string lastKnownSector;
    int    tickWindow;
    int    credThreshold;
    int    spawnTick;
    bool   resolved;
    MissingFlight* next;
};

// Helper functions (Utils.cpp)
int    splitLine(const string& line, char delimiter, string parts[], int maxParts);
int    toInt(const string& text);            // -1 if not a valid number
string intToString(int value);
string trimText(const string& text);
string twoDigits(int value);
string padRight(const string& text, int width);
#endif
