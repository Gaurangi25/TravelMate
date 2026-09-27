#include "TripPlanner.h"

#include "InputUtils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_set>

using namespace std;

void displayCities(const unordered_map<int, City>& cities) {
    cout << "\nList of available cities:\n";
    for (int i = 0; i < CITY_COUNT; ++i) {
        cout << i << " - " << cities.at(i).name << '\n';
    }
}

void findShortestPath(const unordered_map<int, City>& cities, const CityGraph& graph) {
    int src;
    int dest;

    displayCities(cities);
    if (!readInt("\nEnter current city ID (0-" + to_string(CITY_COUNT - 1) + "): ", src) ||
        !readInt("Enter destination city ID (0-" + to_string(CITY_COUNT - 1) + "): ", dest)) {
        return;
    }

    if (!isValidCityId(src) || !isValidCityId(dest)) {
        cout << "Invalid city ID. Please enter a value between 0 and " << CITY_COUNT - 1 << ".\n";
        return;
    }

    dijkstra(src, dest, graph);
}

void displayCityInformation(const unordered_map<int, City>& cities) {
    int cityIndex;

    displayCities(cities);
    if (!readInt("\nEnter the city ID (0-" + to_string(CITY_COUNT - 1) + ") to view information: ", cityIndex)) {
        return;
    }

    if (!isValidCityId(cityIndex)) {
        cout << "Invalid city ID. Please enter a value between 0 and " << CITY_COUNT - 1 << ".\n";
        return;
    }

    const City& city = cities.at(cityIndex);
    cout << "\n-------------------------------------------------------------------\n";
    cout << "City Name : " << city.name << '\n';
    cout << "Weather   : " << city.weather << '\n';
    cout << "-------------------------------------------------------------------\n";
    cout << "Tourist Destinations:\n\n";

    for (const Destination& dest : city.destinations) {
        cout << dest.name << '\n';
        cout << "Description : " << dest.description << '\n';
        cout << "Cost        : Rs. " << dest.cost << '\n';
        cout << "Enjoyment   : " << dest.enjoyment << "/10\n";
        cout << "Duration    : " << dest.duration
             << (dest.duration == 1 ? " hour" : " hours") << "\n\n";
    }
    cout << "-------------------------------------------------------------------\n";
}

void showAllCityDistances(const unordered_map<int, City>& cities, const CityGraph& graph) {
    int src;

    displayCities(cities);
    if (!readInt("\nEnter your current city ID: ", src)) {
        return;
    }

    if (!isValidCityId(src)) {
        cout << "Invalid city ID. Please enter a value between 0 and " << CITY_COUNT - 1 << ".\n";
        return;
    }

    displayShortestDistancesFromSource(src, graph);
}

// 0/1 Knapsack DP: maximizes destination enjoyment under a fixed city budget.
// Time: O(N * min(Budget, MaxCityCost))
// Space: O(N * min(Budget, MaxCityCost))
void optimizeAndDisplayDestinations(const vector<Destination>& destinations, int budget) {
    int n = static_cast<int>(destinations.size());
    int totalPossibleCost = 0;
    for (const auto& dest : destinations) {
        totalPossibleCost += dest.cost;
    }

    int effectiveBudget = min(budget, totalPossibleCost);
    vector<vector<int>> dp(n + 1, vector<int>(effectiveBudget + 1, 0));

    for (int i = 1; i <= n; ++i) {
        const Destination& dest = destinations[i - 1];
        for (int b = 0; b <= effectiveBudget; ++b) {
            int exclude = dp[i - 1][b];
            int include = exclude;
            if (dest.cost <= b) {
                include = dest.enjoyment + dp[i - 1][b - dest.cost];
            }
            dp[i][b] = max(exclude, include);
        }
    }

    int remaining = effectiveBudget;
    int totalCost = 0;
    vector<Destination> selected;

    for (int i = n; i > 0; --i) {
        if (dp[i][remaining] != dp[i - 1][remaining]) {
            const Destination& dest = destinations[i - 1];
            selected.push_back(dest);
            remaining -= dest.cost;
            totalCost += dest.cost;
        }
    }
    reverse(selected.begin(), selected.end());

    cout << "\nMaximum Enjoyment: " << dp[n][effectiveBudget] << '\n';

    if (selected.empty()) {
        cout << "No destination can be selected within the given budget.\n";
        cout << "Total Cost: Rs. 0\n";
        cout << "Remaining Budget: Rs. " << budget << '\n';
        return;
    }

    cout << "\nRecommended Destinations:\n";
    for (size_t i = 0; i < selected.size(); ++i) {
        cout << i + 1 << ". " << selected[i].name << " - Rs. " << selected[i].cost << '\n';
    }
    cout << "\nTotal Cost: Rs. " << totalCost << '\n';
    cout << "Remaining Budget: Rs. " << budget - totalCost << '\n';
}

void optimizeDestinationBudget(const unordered_map<int, City>& cities) {
    int cityId;
    int budget;

    displayCities(cities);
    if (!readInt("\nEnter the city ID you want to visit: ", cityId)) {
        return;
    }

    if (!isValidCityId(cityId)) {
        cout << "Invalid city ID. Please enter a value between 0 and " << CITY_COUNT - 1 << ".\n";
        return;
    }

    if (!readInt("Enter your destination budget: ", budget)) {
        return;
    }

    if (budget < 0) {
        cout << "Budget cannot be negative.\n";
        return;
    }

    cout << "\nDestination Budget Optimizer for " << cities.at(cityId).name << '\n';
    optimizeAndDisplayDestinations(cities.at(cityId).destinations, budget);
}

// TSP with Bitmask DP: finds the minimum round trip across selected cities.
// Time: O(2^K * K^2)
// Space: O(2^K * K)
int tsp(int mask, int pos, const vector<vector<int>>& dist, vector<vector<int>>& dp,
        vector<vector<int>>& parent, int start, int total) {
    if (mask == (1 << total) - 1) {
        return dist[pos][start];
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int best = INF;
    for (int next = 0; next < total; ++next) {
        if (mask & (1 << next)) {
            continue;
        }
        if (dist[pos][next] == INF) {
            continue;
        }

        int subproblemCost = tsp(mask | (1 << next), next, dist, dp, parent, start, total);
        if (subproblemCost == INF) {
            continue;
        }

        int totalCost = dist[pos][next] + subproblemCost;
        if (totalCost < best) {
            best = totalCost;
            parent[mask][pos] = next;
        }
    }

    return dp[mask][pos] = best;
}

void displayItineraryBreakdown(const vector<int>& routeOrder,
                               const unordered_map<int, City>& cities,
                               int totalDistance) {
    cout << "\n=========================================================================================\n";
    cout << "                     Optimal Trip Itinerary Breakdown (Cost & Enjoyment)\n";
    cout << "=========================================================================================\n";

    int grandTotalCost = 0;
    int grandTotalEnjoyment = 0;
    int grandTotalDuration = 0;

    for (size_t i = 0; i < routeOrder.size(); ++i) {
        int cityId = routeOrder[i];
        const City& city = cities.at(cityId);

        cout << "\nStop " << (i + 1) << ": " << city.name 
             << " [Weather: " << city.weather << "]\n";
        cout << "-----------------------------------------------------------------------------------------\n";
        cout << left << setw(38) << "Tourist Destination"
             << setw(14) << "Cost (Rs.)"
             << setw(14) << "Enjoyment"
             << "Duration\n";
        cout << "-----------------------------------------------------------------------------------------\n";

        int cityCost = 0;
        int cityEnjoyment = 0;
        int cityDuration = 0;

        for (const Destination& dest : city.destinations) {
            cout << left << setw(38) << dest.name
                 << "Rs. " << setw(10) << dest.cost
                 << setw(14) << (to_string(dest.enjoyment) + "/10")
                 << dest.duration << (dest.duration == 1 ? " hour" : " hours") << '\n';
            cityCost += dest.cost;
            cityEnjoyment += dest.enjoyment;
            cityDuration += dest.duration;
        }

        cout << "-----------------------------------------------------------------------------------------\n";
        cout << "City Subtotal -> Cost: Rs. " << cityCost
             << " | Enjoyment: " << cityEnjoyment << " pts"
             << " | Sightseeing Time: " << cityDuration << " hrs\n";

        grandTotalCost += cityCost;
        grandTotalEnjoyment += cityEnjoyment;
        grandTotalDuration += cityDuration;
    }

    cout << "\n=========================================================================================\n";
    cout << "                               Overall Itinerary Summary\n";
    cout << "=========================================================================================\n";
    cout << "Total Travel Distance     : " << totalDistance << " km\n";
    cout << "Total Destination Cost    : Rs. " << grandTotalCost << '\n';
    cout << "Total Potential Enjoyment : " << grandTotalEnjoyment << " points\n";
    cout << "Total Sightseeing Duration: " << grandTotalDuration << " hours\n";
    cout << "=========================================================================================\n";
}

void printOptimalRoundTrip(int mask, int pos, const vector<vector<int>>& parent,
                           const vector<int>& citiesToVisit,
                           const unordered_map<int, City>& cities,
                           int startIndex,
                           vector<int>& routeOrder) {
    cout << "\nOptimal Round Trip Route:\n";
    cout << cities.at(citiesToVisit[pos]).name;
    routeOrder.push_back(citiesToVisit[pos]);

    while (mask != (1 << static_cast<int>(citiesToVisit.size())) - 1) {
        int next = parent[mask][pos];
        if (next == -1) {
            cout << "\nUnable to reconstruct the full route.\n";
            return;
        }
        cout << " -> " << cities.at(citiesToVisit[next]).name;
        routeOrder.push_back(citiesToVisit[next]);
        mask |= (1 << next);
        pos = next;
    }

    cout << " -> " << cities.at(citiesToVisit[startIndex]).name << '\n';
}

void planOptimalRoundTrip(const unordered_map<int, City>& cities, const CityGraph& graph) {
    int selectedCount;

    cout << "\nOptimal Round Trip Planner\n";
    if (!readInt("Enter number of cities to visit (1-" + to_string(CITY_COUNT) + "): ", selectedCount)) {
        return;
    }

    if (selectedCount <= 0 || selectedCount > CITY_COUNT) {
        cout << "Number of selected cities must be between 1 and " << CITY_COUNT << ".\n";
        return;
    }

    displayCities(cities);

    vector<int> citiesToVisit;
    unordered_set<int> selectedIds;

    cout << "Enter city IDs to visit:\n";
    for (int i = 0; i < selectedCount; ++i) {
        int cityId;
        if (!readInt("City " + to_string(i + 1) + ": ", cityId)) {
            return;
        }

        if (!isValidCityId(cityId)) {
            cout << "Invalid city ID skipped: " << cityId << ".\n";
            continue;
        }

        if (selectedIds.count(cityId)) {
            cout << "Duplicate city skipped: " << cityNames[cityId] << ".\n";
            continue;
        }

        citiesToVisit.push_back(cityId);
        selectedIds.insert(cityId);
    }

    int startCity;
    if (!readInt("Enter starting city ID: ", startCity)) {
        return;
    }

    if (!isValidCityId(startCity)) {
        cout << "Invalid starting city ID.\n";
        return;
    }

    if (!selectedIds.count(startCity)) {
        citiesToVisit.insert(citiesToVisit.begin(), startCity);
        selectedIds.insert(startCity);
    }

    if (citiesToVisit.empty()) {
        cout << "No valid cities were selected.\n";
        return;
    }

    int k = static_cast<int>(citiesToVisit.size());
    vector<vector<int>> allPairs = computeAllPairsShortestDistances(graph);
    vector<vector<int>> reduced(k, vector<int>(k, INF));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            reduced[i][j] = allPairs[citiesToVisit[i]][citiesToVisit[j]];
            if (reduced[i][j] == INF) {
                cout << "No valid round trip exists for the selected cities.\n";
                return;
            }
        }
    }

    int startIndex = 0;
    for (int i = 0; i < k; ++i) {
        if (citiesToVisit[i] == startCity) {
            startIndex = i;
            break;
        }
    }

    vector<vector<int>> dp(1 << k, vector<int>(k, -1));
    vector<vector<int>> parent(1 << k, vector<int>(k, -1));

    int result = tsp(1 << startIndex, startIndex, reduced, dp, parent, startIndex, k);

    if (result == INF) {
        cout << "No valid round trip exists for the selected cities.\n";
        return;
    }

    cout << "\nMinimum Travel Distance: " << result << " km\n";
    vector<int> routeOrder;
    printOptimalRoundTrip(1 << startIndex, startIndex, parent, citiesToVisit, cities, startIndex, routeOrder);

    int viewBreakdownChoice = 1;
    if (readInt("\nView destination enjoyment, price, and duration breakdown for this route? (1 = Yes, 0 = No): ", viewBreakdownChoice) && viewBreakdownChoice == 1) {
        displayItineraryBreakdown(routeOrder, cities, result);
    }
}
