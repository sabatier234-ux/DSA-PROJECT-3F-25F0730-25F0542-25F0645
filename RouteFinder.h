// RouteFinder.h - Module 8: Dijkstra with custom min-heap (Student 3)
#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H
#include "Common.h"
#include "SpaceGraph.h"

// One entry in the Dijkstra priority heap
struct DistNode {
    int sector;
    int distance;
};

// Custom min-heap keyed by shortest distance so far
class DistHeap {
private:
    DistNode data[MAX_HEAP];
    int      size;
    void heapifyUp(int index);
    void heapifyDown(int index);
public:
    DistHeap();
    void     push(int sector, int distance);
    DistNode pop();
    bool     isEmpty();
};

class RouteFinder {
private:
    SpaceGraph* graph;
public:
    RouteFinder(SpaceGraph* g);

    // Dijkstra using the adjacency matrix, skips disabled corridors
    Route findFastestRoute(const string& sourceSector, const string& destinationRunway);
    void  printRoute(const Route& route);
    Route findNearestEmergencyRunway(const string& sourceSector);   // Runway 09 or 12
};

#endif
