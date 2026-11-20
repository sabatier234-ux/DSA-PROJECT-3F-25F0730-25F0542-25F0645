#include "SpaceGraph.h"

SpaceGraph::SpaceGraph() {
    sectorCount = 0;
    towerDegraded = false;
    adjMatrix = new int*[MAX_SECTORS];
    for (int i = 0; i < MAX_SECTORS; i++) {
        adjMatrix[i] = new int[MAX_SECTORS];
        for (int j = 0; j < MAX_SECTORS; j++) adjMatrix[i][j] = 0;
        adjList[i] = nullptr;
        isRunwayFlag[i] = false;
    }
}

SpaceGraph::~SpaceGraph() {
    for (int i = 0; i < MAX_SECTORS; i++) {
        while (adjList[i] != nullptr) {
            AdjNode* next = adjList[i]->next;
            delete adjList[i];
            adjList[i] = next;
        }
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

int SpaceGraph::addSector(const string& name) {
    for (int i = 0; i < sectorCount; i++)
        if (sectorNames[i] == name) return i;
    if (sectorCount >= MAX_SECTORS) return -1;
    sectorNames[sectorCount] = name;
    isRunwayFlag[sectorCount] = (name.compare(0, 6, "Runway") == 0);
    sectorCount++;
    return sectorCount - 1;
}

void SpaceGraph::addEdge(int from, int to, int weight) {
    AdjNode* node = new AdjNode();
    node->destination = to;
    node->weight = weight;
    node->disabled = false;
    node->next = nullptr;
    if (adjList[from] == nullptr) {
        adjList[from] = node;
    } else {
        AdjNode* last = adjList[from];
        while (last->next != nullptr) last = last->next;
        last->next = node;
    }
}

AdjNode* SpaceGraph::findEdge(int from, int to) {
    for (AdjNode* n = adjList[from]; n != nullptr; n = n->next)
        if (n->destination == to) return n;
    return nullptr;
}

void SpaceGraph::addCorridor(const string& from, const string& to, int weightTicks) {
    int a = addSector(from);
    int b = addSector(to);
    if (a < 0 || b < 0 || a == b) return;
    if (findEdge(a, b) != nullptr) return;
    addEdge(a, b, weightTicks);
    addEdge(b, a, weightTicks);
    adjMatrix[a][b] = weightTicks;
    adjMatrix[b][a] = weightTicks;
}

int SpaceGraph::getWeight(int from, int to) {
    if (from < 0 || to < 0 || from >= sectorCount || to >= sectorCount) return 0;
    return adjMatrix[from][to];
}

int SpaceGraph::getSectorCount() { return sectorCount; }

int SpaceGraph::getSectorIndex(const string& name) {
    if (name == "") return -1;
    for (int i = 0; i < sectorCount; i++)
        if (sectorNames[i] == name) return i;
    for (int i = 0; i < sectorCount; i++)
        if (sectorNames[i].compare(0, name.size(), name) == 0) return i;
    return -1;
}

string SpaceGraph::getSectorName(int index) {
    if (index < 0 || index >= sectorCount) return "";
    return sectorNames[index];
}

bool SpaceGraph::isRunway(int index) {
    if (index < 0 || index >= sectorCount) return false;
    return isRunwayFlag[index];
}

AdjNode* SpaceGraph::getNeighbors(int index) { return adjList[index]; }

void SpaceGraph::disableCorridor(int from, int to) {
    AdjNode* a = findEdge(from, to);
    AdjNode* b = findEdge(to, from);
    if (a != nullptr) a->disabled = true;
    if (b != nullptr) b->disabled = true;
    adjMatrix[from][to] = 0;
    adjMatrix[to][from] = 0;
}

void SpaceGraph::enableCorridor(int from, int to) {
    AdjNode* a = findEdge(from, to);
    AdjNode* b = findEdge(to, from);
    if (a != nullptr) {
        a->disabled = false;
        adjMatrix[from][to] = a->weight;
    }
    if (b != nullptr) {
        b->disabled = false;
        adjMatrix[to][from] = b->weight;
    }
}

void SpaceGraph::setTowerDegraded(bool value) { towerDegraded = value; }
bool SpaceGraph::isTowerDegraded() { return towerDegraded; }

void SpaceGraph::displayAdjacencyList() {
    cout << "Adjacency list (neighbor, ticks):\n";
    for (int i = 0; i < sectorCount; i++) {
        cout << "  " << sectorNames[i] << " ->";
        for (AdjNode* n = adjList[i]; n != nullptr; n = n->next) {
            cout << " [" << sectorNames[n->destination] << ", " << n->weight;
            if (n->disabled) cout << ", DISABLED";
            cout << "]";
        }
        cout << "\n";
    }
}

void SpaceGraph::displayAdjacencyMatrix() {
    cout << "Adjacency matrix (0 = no corridor):\n      ";
    for (int j = 0; j < sectorCount; j++) cout << padRight(intToString(j), 4);
    cout << "\n";
    for (int i = 0; i < sectorCount; i++) {
        cout << padRight("[" + intToString(i) + "]", 6);
        for (int j = 0; j < sectorCount; j++) cout << padRight(intToString(adjMatrix[i][j]), 4);
        cout << " " << sectorNames[i] << "\n";
    }
}
