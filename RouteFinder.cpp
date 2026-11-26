#include "RouteFinder.h"

const int INFINITE_COST = 9999;

DistHeap::DistHeap() { size = 0; }

void DistHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (data[index].distance >= data[parent].distance) break;
        DistNode temp = data[index];
        data[index] = data[parent];
        data[parent] = temp;
        index = parent;
    }
}

void DistHeap::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < size && data[left].distance < data[smallest].distance) smallest = left;
        if (right < size && data[right].distance < data[smallest].distance) smallest = right;
        if (smallest == index) break;
        DistNode temp = data[index];
        data[index] = data[smallest];
        data[smallest] = temp;
        index = smallest;
    }
}

void DistHeap::push(int sector, int distance) {
    if (size >= MAX_HEAP) return;
    data[size].sector = sector;
    data[size].distance = distance;
    heapifyUp(size);
    size++;
}

DistNode DistHeap::pop() {
    DistNode top = data[0];
    size--;
    data[0] = data[size];
    heapifyDown(0);
    return top;
}

bool DistHeap::isEmpty() { return size == 0; }

RouteFinder::RouteFinder(SpaceGraph* g) { graph = g; }

Route RouteFinder::findFastestRoute(const string& sourceSector, const string& destinationRunway) {
    Route route;
    route.pathLength = 0;
    route.totalCost = 0;
    route.found = false;

    int n = graph->getSectorCount();
    int source = graph->getSectorIndex(sourceSector);
    int target = graph->getSectorIndex(destinationRunway);
    if (source < 0 || target < 0) return route;

    int dist[MAX_SECTORS];
    int parent[MAX_SECTORS];
    bool done[MAX_SECTORS];
    for (int i = 0; i < MAX_SECTORS; i++) {
        dist[i] = INFINITE_COST;
        parent[i] = -1;
        done[i] = false;
    }
    dist[source] = 0;

    DistHeap heap;
    heap.push(source, 0);
    while (!heap.isEmpty()) {
        DistNode current = heap.pop();
        int u = current.sector;
        if (done[u]) continue;
        done[u] = true;
        if (u == target) break;
        for (int v = 0; v < n; v++) {
            int w = graph->getWeight(u, v);
            if (w > 0 && !done[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                heap.push(v, dist[v]);
            }
        }
    }
    if (dist[target] >= INFINITE_COST) return route;

    int reversed[MAX_SECTORS];
    int count = 0;
    for (int v = target; v != -1; v = parent[v]) reversed[count++] = v;
    for (int i = 0; i < count; i++) route.sectors[i] = graph->getSectorName(reversed[count - 1 - i]);
    route.pathLength = count;
    route.totalCost = dist[target];
    route.found = true;
    return route;
}

void RouteFinder::printRoute(const Route& route) {
    if (!route.found) {
        cout << "No route available.\n";
        return;
    }
    cout << "Route: ";
    for (int i = 0; i < route.pathLength; i++) {
        cout << route.sectors[i];
        if (i < route.pathLength - 1) cout << " -> ";
    }
    cout << "\nTotal travel time: " << route.totalCost << " ticks\n";
}

Route RouteFinder::findNearestEmergencyRunway(const string& sourceSector) {
    Route a = findFastestRoute(sourceSector, "Runway 09");
    Route b = findFastestRoute(sourceSector, "Runway 12");
    if (!a.found) return b;
    if (!b.found) return a;
    return (a.totalCost <= b.totalCost) ? a : b;
}
