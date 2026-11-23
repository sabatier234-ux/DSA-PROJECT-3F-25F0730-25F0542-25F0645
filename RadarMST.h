
#ifndef RADARMST_H
#define RADARMST_H
#include "Common.h"
#include "SpaceGraph.h"

struct Edge {
    int from;
    int to;
    int weight;
};

class UnionFind {
private:
    int parent[MAX_SECTORS];
    int rankArr[MAX_SECTORS];
public:
    UnionFind(int n);
    int  find(int x);              
    bool unite(int a, int b);      
};

class RadarMST {
private:
    SpaceGraph* graph;
    Edge allEdges[MAX_SECTORS * MAX_SECTORS];
    int  edgeCount;
    Edge mstEdges[MAX_SECTORS];
    int  mstCount;
    int  totalCost;

    void collectEdges();                      
    void sortEdges();                         
    bool isConnectedWithout(int skipIndex);   

public:
    RadarMST(SpaceGraph* g);

    void computeMST();
    void displayMST();
    bool verifyConnectivity();    
};

#endif
