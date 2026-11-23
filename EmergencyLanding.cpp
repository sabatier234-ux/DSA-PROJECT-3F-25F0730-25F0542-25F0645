#include "EmergencyLanding.h"

EmergencyLanding::EmergencyLanding() {
    qFront = 0;
    qRear = 0;
    qCount = 0;
    heapSize = 0;
}

bool EmergencyLanding::isHigherPriority(Flight* a, Flight* b) {
    if (a->priorityLevel != b->priorityLevel) return a->priorityLevel < b->priorityLevel;
    return a->arrivalTick < b->arrivalTick;
}

void EmergencyLanding::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!isHigherPriority(heapArray[index], heapArray[parent])) break;
        Flight* temp = heapArray[index];
        heapArray[index] = heapArray[parent];
        heapArray[parent] = temp;
        index = parent;
    }
}

void EmergencyLanding::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;          //index of most urgent node
        if (left < heapSize && isHigherPriority(heapArray[left], heapArray[best])) best = left;
        if (right < heapSize && isHigherPriority(heapArray[right], heapArray[best])) best = right;
        if (best == index) break;           
        Flight* temp = heapArray[index];
        heapArray[index] = heapArray[best];
        heapArray[best] = temp;
        index = best;
    }
}
// Normal queue using circular array
void EmergencyLanding::enqueueNormal(Flight* flight) {
    if (qCount >= MAX_HEAP) return;
    normalQueue[qRear] = flight;
    qRear = (qRear + 1) % MAX_HEAP;  //wrap around to reuse slots
    qCount++;
}

Flight* EmergencyLanding::dequeueNormal() {
    if (qCount == 0) return nullptr;
    Flight* flight = normalQueue[qFront];
    qFront = (qFront + 1) % MAX_HEAP;
    qCount--;
    return flight;
}

Flight* EmergencyLanding::frontNormal() {      //peek
    if (qCount == 0) return nullptr;
    return normalQueue[qFront];
}

bool EmergencyLanding::isEmptyNormal() { return qCount == 0; }

void EmergencyLanding::displayNormalQueue() {
    cout << "Normal landing queue (" << qCount << "):\n";
    for (int i = 0; i < qCount; i++) {
        Flight* f = normalQueue[(qFront + i) % MAX_HEAP];
        cout << "  " << i + 1 << ". " << f->callsign << " -> " << f->assignedRunway << " (fuel " << f->fuelRemaining << ")\n";
    }
}

void EmergencyLanding::removeFromQueue(const string& callsign) {
    int total = qCount;
    for (int i = 0; i < total; i++) {
        Flight* f = dequeueNormal();
        if (f->callsign != callsign) enqueueNormal(f);
    }
}
//Emergency using min heap
void EmergencyLanding::insertEmergency(Flight* flight) {
    if (heapSize >= MAX_HEAP) return;
    heapArray[heapSize] = flight;
    heapifyUp(heapSize);
    heapSize++;
}

Flight* EmergencyLanding::extractMin() {
    if (heapSize == 0) return nullptr;
    Flight* top = heapArray[0];
    heapSize--;
    heapArray[0] = heapArray[heapSize];
    heapifyDown(0);
    return top;
}

Flight* EmergencyLanding::peekMin() {
    if (heapSize == 0) return nullptr;
    return heapArray[0];
}

bool EmergencyLanding::isEmptyHeap() { return heapSize == 0; }


// prints the heap in array order 
void EmergencyLanding::displayHeap() {
    cout << "Emergency heap (" << heapSize << "):\n";
    for (int i = 0; i < heapSize; i++) {
        Flight* f = heapArray[i];
        cout << "  " << f->callsign << " priority " << f->priorityLevel << ", arrival tick " << f->arrivalTick << "\n";
    }
}

void EmergencyLanding::removeFromHeap(const string& callsign) {
    for (int i = 0; i < heapSize; i++) {
        if (heapArray[i]->callsign == callsign) {
            heapSize--;
            heapArray[i] = heapArray[heapSize];
            rebuildHeap();
            return;
        }
    }
}

void EmergencyLanding::rebuildHeap() {
    for (int i = heapSize / 2 - 1; i >= 0; i--) heapifyDown(i);
}

Flight* EmergencyLanding::processNextLanding() {
    if (!isEmptyNormal()) return dequeueNormal();
    if (!isEmptyHeap()) return extractMin();
    return nullptr;
}
