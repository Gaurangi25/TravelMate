#include "GraphAlgorithms.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

void addEdge(CityGraph& graph, int u, int v, int distance) {
    graph[u].push_back({v, distance});
    graph[v].push_back({u, distance});
}

CityGraph createCityGraph() {
    CityGraph graph(CITY_COUNT);

    addEdge(graph, 0, 1, 1400);
    addEdge(graph, 0, 2, 280);
    addEdge(graph, 0, 3, 230);
    addEdge(graph, 0, 4, 1500);
    addEdge(graph, 0, 5, 2150);
    addEdge(graph, 0, 6, 1580);
    addEdge(graph, 0, 8, 820);
    addEdge(graph, 0, 9, 450);
    addEdge(graph, 0, 10, 2200);
    addEdge(graph, 0, 14, 240);
    addEdge(graph, 1, 2, 1140);
    addEdge(graph, 1, 4, 2000);
    addEdge(graph, 1, 5, 980);
    addEdge(graph, 1, 6, 710);
    addEdge(graph, 1, 10, 1330);
    addEdge(graph, 1, 12, 150);
    addEdge(graph, 1, 13, 590);
    addEdge(graph, 2, 3, 240);
    addEdge(graph, 2, 7, 390);
    addEdge(graph, 3, 8, 610);
    addEdge(graph, 4, 6, 1500);
    addEdge(graph, 4, 10, 1670);
    addEdge(graph, 4, 15, 620);
    addEdge(graph, 4, 8, 680);
    addEdge(graph, 5, 6, 570);
    addEdge(graph, 5, 10, 350);
    addEdge(graph, 5, 11, 150);
    addEdge(graph, 5, 12, 840);
    addEdge(graph, 6, 10, 630);
    addEdge(graph, 7, 13, 640);

    return graph;
}

// Floyd-Warshall algorithm: computes shortest distances between every pair of cities.
// Time: O(V^3)
// Space: O(V^2)
vector<vector<int>> computeAllPairsShortestDistances(const CityGraph& graph) {
    vector<vector<int>> dist(CITY_COUNT, vector<int>(CITY_COUNT, INF));

    for (int i = 0; i < CITY_COUNT; ++i) {
        dist[i][i] = 0;
    }

    for (int u = 0; u < CITY_COUNT; ++u) {
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            dist[u][v] = min(dist[u][v], weight);
        }
    }

    for (int k = 0; k < CITY_COUNT; ++k) {
        for (int i = 0; i < CITY_COUNT; ++i) {
            for (int j = 0; j < CITY_COUNT; ++j) {
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

// Dijkstra's algorithm: finds the shortest path from a source city to a
// destination city in a weighted graph with non-negative edges.
// Time: O((V + E) log V)
// Space: O(V)
void dijkstra(int src, int dest, const CityGraph& graph) {
    vector<int> dist(CITY_COUNT, INF);
    vector<int> parent(CITY_COUNT, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int curDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (curDist > dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No path between " << cityNames[src] << " and " << cityNames[dest] << ".\n";
        return;
    }

    vector<int> path;
    for (int at = dest; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "\nShortest distance from " << cityNames[src] << " to "
         << cityNames[dest] << ": " << dist[dest] << " km\n";
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << cityNames[path[i]];
        if (i + 1 < path.size()) {
            cout << " -> ";
        }
    }
    cout << '\n';
}

void displayShortestDistancesFromSource(int src, const CityGraph& graph) {
    vector<vector<int>> dist = computeAllPairsShortestDistances(graph);

    cout << "\nShortest distances from " << cityNames[src] << ":\n";
    for (int dest = 0; dest < CITY_COUNT; ++dest) {
        if (dist[src][dest] == INF) {
            cout << "No path from " << cityNames[src] << " to " << cityNames[dest] << ".\n";
        } else {
            cout << "Distance from " << cityNames[src] << " to "
                 << cityNames[dest] << ": " << dist[src][dest] << " km\n";
        }
    }
}
