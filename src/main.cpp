#include "GraphAlgorithms.h"
#include "InputUtils.h"
#include "Models.h"
#include "Splitwise.h"
#include "TripPlanner.h"
#include "UserManager.h"

#include <iostream>
#include <unordered_map>

using namespace std;

void printMenu() {
    cout << "\n=========================================================\n";
    cout << "              TravelMate - Main Menu\n";
    cout << "=========================================================\n";
    cout << "1. View My Profile\n";
    cout << "2. Find Shortest Path Between Cities\n";
    cout << "3. Plan Optimal Round Trip\n";
    cout << "4. View All Cities\n";
    cout << "5. View City Information\n";
    cout << "6. View Shortest Distances From a City\n";
    cout << "7. Destination Budget Optimizer\n";
    cout << "8. Group Expense Split\n";
    cout << "9. Exit\n";
    cout << "=========================================================\n";
}

void showMainMenu(const User& user, const unordered_map<int, City>& cities, const CityGraph& graph) {
    int choice;

    do {
        printMenu();
        if (!readInt("Choose an option: ", choice)) {
            choice = 0;
            continue;
        }

        switch (choice) {
        case 1:
            user.displayProfile();
            break;
        case 2:
            findShortestPath(cities, graph);
            break;
        case 3:
            planOptimalRoundTrip(cities, graph);
            break;
        case 4:
            displayCities(cities);
            break;
        case 5:
            displayCityInformation(cities);
            break;
        case 6:
            showAllCityDistances(cities, graph);
            break;
        case 7:
            optimizeDestinationBudget(cities);
            break;
        case 8:
            manageGroupExpenses();
            break;
        case 9:
            cout << "\nExiting TravelMate. Have a great journey!\n";
            break;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 9);
}

int main() {
    loadUsers();

    unordered_map<int, City> cities = createCitiesData();
    CityGraph graph = createCityGraph();

    int choice;

    do {
        cout << "\n=========================================================\n";
        cout << "Welcome to TravelMate - The Tourist Guide Navigator\n";
        cout << "=========================================================\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        if (!readInt("Choose an option: ", choice)) {
            choice = 0;
            continue;
        }

        bool verified = false;
        string email;

        switch (choice) {
        case 1:
            verified = signup(email);
            break;
        case 2:
            verified = login(email);
            break;
        case 3:
            cout << "Thank you for using TravelMate.\n";
            break;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }

        if (verified) {
            showMainMenu(users.at(email), cities, graph);
        }
    } while (choice != 3);

    return 0;
}
