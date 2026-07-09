#pragma once

#include "Models.h"

#include <utility>
#include <vector>

using namespace std;

using CityGraph = vector<vector<pair<int, int>>>;

void addEdge(CityGraph& graph, int u, int v, int distance);
CityGraph createCityGraph();
vector<vector<int>> computeAllPairsShortestDistances(const CityGraph& graph);
void dijkstra(int src, int dest, const CityGraph& graph);
void displayShortestDistancesFromSource(int src, const CityGraph& graph);
