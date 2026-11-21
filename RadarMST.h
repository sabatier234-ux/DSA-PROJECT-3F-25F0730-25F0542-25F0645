// RadarMST.h - Module 9: minimum spanning tree with Kruskal + union-find (Student 3)
#ifndef RADARMST_H
#define RADARMST_H
#include "Common.h"
#include "SpaceGraph.h"

struct Edge {
    int from;
    int to;
    int weight;
};

// Union-find (disjoint set) used by Kruskal
class UnionFind {
private:
    int parent[MAX_SECTORS];
    int rankArr[MAX_SECTORS];
public:
    UnionFind(int n);
    int  find(int x);              // with path compression
    bool unite(int a, int b);      // false if already in the same set
};

class RadarMST {
private:
    SpaceGraph* graph;
    Edge allEdges[MAX_SECTORS * MAX_SECTORS];
    int  edgeCount;
    Edge mstEdges[MAX_SECTORS];
    int  mstCount;
    int  totalCost;

    void collectEdges();                      // read edges from the graph
    void sortEdges();                         // own sort (no std::sort)
    bool isConnectedWithout(int skipIndex);   // helper for verification

public:
    RadarMST(SpaceGraph* g);

    void computeMST();
    void displayMST();
    bool verifyConnectivity();    // removes each MST edge and shows the network disconnects
};

#endif
