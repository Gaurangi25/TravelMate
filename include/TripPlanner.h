#pragma once

#include "GraphAlgorithms.h"
#include "Models.h"

#include <unordered_map>

using namespace std;

void displayCities(const unordered_map<int, City>& cities);
void findShortestPath(const unordered_map<int, City>& cities, const CityGraph& graph);
void displayCityInformation(const unordered_map<int, City>& cities);
void showAllCityDistances(const unordered_map<int, City>& cities, const CityGraph& graph);
void optimizeDestinationBudget(const unordered_map<int, City>& cities);
void optimizeAndDisplayDestinations(const vector<Destination>& destinations, int budget);
void planOptimalRoundTrip(const unordered_map<int, City>& cities, const CityGraph& graph);
