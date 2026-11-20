#ifndef SPACEGRAPH_H
#define SPACEGRAPH_H
#include "Common.h"

struct AdjNode {
    int      destination;
    int      weight;
    bool     disabled;
    AdjNode* next;
};

class SpaceGraph {
private:
    string   sectorNames[MAX_SECTORS];
    bool     isRunwayFlag[MAX_SECTORS];
    AdjNode* adjList[MAX_SECTORS];
    int**    adjMatrix;
    int      sectorCount;
    bool     towerDegraded;

    void     addEdge(int from, int to, int weight);
    AdjNode* findEdge(int from, int to);

public:
    SpaceGraph();
    ~SpaceGraph();

    int    addSector(const string& name);
    void   addCorridor(const string& from, const string& to, int weightTicks);
    int    getWeight(int from, int to);
    int    getSectorCount();
    int    getSectorIndex(const string& name);   // exact match first, then prefix match
    string getSectorName(int index);
    bool   isRunway(int index);
    AdjNode* getNeighbors(int index);

    void disableCorridor(int from, int to);
    void enableCorridor(int from, int to);
    void setTowerDegraded(bool value);
    bool isTowerDegraded();

    void displayAdjacencyList();
    void displayAdjacencyMatrix();
};

#endif
