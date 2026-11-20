#include "RadarMST.h"

UnionFind::UnionFind(int n) {
    (void)n;
    for (int i = 0; i < MAX_SECTORS; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

int UnionFind::find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

bool UnionFind::unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA == rootB) return false;
    if (rankArr[rootA] < rankArr[rootB]) parent[rootA] = rootB;
    else if (rankArr[rootA] > rankArr[rootB]) parent[rootB] = rootA;
    else {
        parent[rootB] = rootA;
        rankArr[rootA]++;
    }
    return true;
}

RadarMST::RadarMST(SpaceGraph* g) {
    graph = g;
    edgeCount = 0;
    mstCount = 0;
    totalCost = 0;
}

void RadarMST::collectEdges() {
    edgeCount = 0;
    int n = graph->getSectorCount();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int w = graph->getWeight(i, j);
            if (w > 0) {
                allEdges[edgeCount].from = i;
                allEdges[edgeCount].to = j;
                allEdges[edgeCount].weight = w;
                edgeCount++;
            }
        }
    }
}

void RadarMST::sortEdges() {
    for (int i = 1; i < edgeCount; i++) {
        Edge key = allEdges[i];
        int j = i - 1;
        while (j >= 0 && allEdges[j].weight > key.weight) {
            allEdges[j + 1] = allEdges[j];
            j--;
        }
        allEdges[j + 1] = key;
    }
}

bool RadarMST::isConnectedWithout(int skipIndex) {
    int n = graph->getSectorCount();
    UnionFind uf(n);
    int unions = 0;
    for (int i = 0; i < mstCount; i++) {
        if (i == skipIndex) continue;
        if (uf.unite(mstEdges[i].from, mstEdges[i].to)) unions++;
    }
    return (n - unions) == 1;
}

void RadarMST::computeMST() {
    collectEdges();
    sortEdges();
    UnionFind uf(graph->getSectorCount());
    mstCount = 0;
    totalCost = 0;
    for (int i = 0; i < edgeCount; i++) {
        if (uf.unite(allEdges[i].from, allEdges[i].to)) {
            mstEdges[mstCount++] = allEdges[i];
            totalCost += allEdges[i].weight;
        }
    }
}

void RadarMST::displayMST() {
    cout << "Minimum radar coverage (Kruskal):\n";
    for (int i = 0; i < mstCount; i++) {
        cout << "  " << graph->getSectorName(mstEdges[i].from) << " -- " << graph->getSectorName(mstEdges[i].to)
             << " (" << mstEdges[i].weight << ")\n";
    }
    cout << "Corridors selected: " << mstCount << "   Total cost: " << totalCost << "\n";
}

bool RadarMST::verifyConnectivity() {
    int n = graph->getSectorCount();
    cout << "Network connected with all MST edges: " << (isConnectedWithout(-1) ? "YES" : "NO") << "\n";
    bool allDisconnect = true;
    for (int i = 0; i < mstCount; i++) {
        bool connected = isConnectedWithout(i);
        cout << "  Remove " << graph->getSectorName(mstEdges[i].from) << " -- "
             << graph->getSectorName(mstEdges[i].to) << ": "
             << (connected ? "still connected" : "DISCONNECTED") << "\n";
        if (connected) allDisconnect = false;
    }
    (void)n;
    cout << (allDisconnect ? "Proof: every MST edge is needed, so the tree is minimal.\n"
                           : "Some edge is not needed.\n");
    return allDisconnect;
}
