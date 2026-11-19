#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "Common.h"
class Registration {
private:
    Flight*   flightHead;
    Flight*   flightTail;

public:
    Registration();
    ~Registration();

    void    addFlight(Flight* flight);
    bool    removeFlight(const string& callsign);
    void    updateAllFlights();
    void    displayAllFlights();
};

#endif
