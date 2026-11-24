#include "Registration.h"
//implemented by singly list
Registration::Registration() {
    flightHead = nullptr;
    flightTail = nullptr;
    crewHead = nullptr;
    crewTail = nullptr;
    flightCount = 0;
}

Registration::~Registration() {
    while (flightHead != nullptr) {
        Flight* next = flightHead->next;
        delete flightHead;
        flightHead = next;
    }
    while (crewHead != nullptr) {
        Crew* next = crewHead->next;
        delete crewHead;
        crewHead = next;
    }
}

void Registration::addFlight(Flight* flight) {
    flight->next = nullptr;
    if (flightHead == nullptr) flightHead = flight;
    else flightTail->next = flight;
    flightTail = flight;
    hashTable.insert(flight->callsign, flight);
    flightCount++;
}

bool Registration::removeFlight(const string& callsign) {
    Flight* previous = nullptr;
    Flight* current = flightHead;
    while (current != nullptr && current->callsign != callsign) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) return false;
    if (previous != nullptr) previous->next = current->next;
    else flightHead = current->next;
    if (current == flightTail) flightTail = previous;
    hashTable.remove(callsign);
    delete current;
    flightCount--;
    return true;
}

void Registration::updateAllFlights() {
    for (Flight* f = flightHead; f != nullptr; f = f->next) {
        if (f->status == 0 || f->status == 3) {
            int old = f->fuelRemaining;
            if (f->fuelRemaining > 0) f->fuelRemaining--;
            cout << "  " << f->callsign << " fuel " << old << " -> " << f->fuelRemaining << "\n";
        }
    }
}

void Registration::displayAllFlights() {
    cout << padRight("Callsign", 9) << padRight("Type", 17) << padRight("Sector", 22)
         << padRight("Runway", 12) << padRight("Fuel", 6) << "Pri\n";
    for (Flight* f = flightHead; f != nullptr; f = f->next) {
        if (f->status != 0 && f->status != 3) continue;
        cout << padRight(f->callsign, 9) << padRight(f->aircraftType, 17) << padRight(f->currentSector, 22)
             << padRight(f->assignedRunway, 12) << padRight(intToString(f->fuelRemaining), 6)
             << f->priorityLevel << "\n";
    }
}
void Registration::addCrew(Crew* crew) {
    crew->next = nullptr;
    if (crewHead == nullptr) crewHead = crew;
    else crewTail->next = crew;
    crewTail = crew;
}

void Registration::displayAllCrew() {
    cout << padRight("ID", 8) << padRight("Name", 24) << padRight("Role", 20) << "Flight\n";
    for (Crew* c = crewHead; c != nullptr; c = c->next)
        cout << padRight(c->employeeID, 8) << padRight(c->name, 24) << padRight(c->role, 20)
             << c->assignedCallsign << "\n";
}

Flight* Registration::findFlight(const string& callsign) {
    return hashTable.find(callsign);
}

string Registration::getPilotName(const string& callsign) {
    for (Crew* c = crewHead; c != nullptr; c = c->next) {
        if (c->assignedCallsign == callsign &&
            (c->role.find("Captain") != string::npos || c->role.find("Pilot") != string::npos))
            return c->name;
    }
    return "Unknown";
}

Flight* Registration::getHead() { return flightHead; }
int Registration::getFlightCount() { return flightCount; }
HashTable& Registration::getHashTable() { return hashTable; }

