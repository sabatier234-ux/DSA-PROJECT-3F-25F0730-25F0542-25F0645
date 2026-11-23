#ifndef EMERGENCYLANDING_H
#define EMERGENCYLANDING_H
#include "Common.h"

class EmergencyLanding {
private:
    // Normal queue using circular arr
    Flight* normalQueue[MAX_HEAP];
    int     qFront, qRear, qCount;

   
    Flight* heapArray[MAX_HEAP];
    int     heapSize;

    bool isHigherPriority(Flight* a, Flight* b);   
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    EmergencyLanding();

    // Queue operations
    void    enqueueNormal(Flight* flight);
    Flight* dequeueNormal();
    Flight* frontNormal();
    bool    isEmptyNormal();
    void    displayNormalQueue();
    void    removeFromQueue(const string& callsign);   

    // Heap operations
    void    insertEmergency(Flight* flight);
    Flight* extractMin();
    Flight* peekMin();
    bool    isEmptyHeap();
    void    displayHeap();
    void    removeFromHeap(const string& callsign);
    void    rebuildHeap();                       

    Flight* processNextLanding();
};

#endif
