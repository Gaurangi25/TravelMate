#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

class User
{
public:
    string name;
    string email;
    string password;

    User() {}

    User(string n, string e, string p)
    {
        name = n;
        email = e;
        password = p;
    }

    void displayProfile()
    {
        cout << "\n----------------------------\n";
        cout << "      User Profile\n";
        cout << "----------------------------\n";
        cout << "   Name  : " << name << endl;
        cout << "   Email : " << email << endl;
        cout << "----------------------------\n\n";
    }
};

// Stores users with email as key for quick login/signup access
unordered_map<string, User> users;

// Class to represent a Tourist Destination
class Destination
{
public:
    string name;
    int cost;      // Cost to visit this destination
    int enjoyment; // Enjoyment value of this destination
    string description;

    Destination(string n, int c, int e, string desc)
    {
        name = n;
        cost = c;
        enjoyment = e;
        description = desc;
    }

    static vector<Destination> defineDestinations()
    {
        vector<Destination> destinations = {
            Destination("Museum", 20, 8, "A cultural experience with historical artifacts"),
            Destination("Beach", 10, 7, "Relax on the sandy shores"),
            Destination("Mountain Trek", 40, 10, "Challenging hike with amazing views"),
            Destination("Amusement Park", 50, 9, "Exciting rides and fun attractions"),
            Destination("Local Market", 5, 6, "Experience local culture and food")};
        return destinations;
    }
};

// Class to represent a City
class City
{
public:
    string name;
    int id;
    vector<Destination> destinations;

    City(string n, int i)
    {
        name = n;
        id = i;
    }

    void addDestination(Destination dest)
    {
        destinations.push_back(dest);
    }

    // Function to define cities
    static vector<City> defineCities()
    {
        vector<City> cities = {
            City("A", 0),
            City("B", 1),
            City("C", 2),
            City("D", 3),
            City("E", 4)};

        // Add destinations to cities
        vector<Destination> allDestinations = Destination::defineDestinations();
        cities[0].addDestination(allDestinations[0]); // Museum in City A
        cities[1].addDestination(allDestinations[1]); // Beach in City B
        cities[2].addDestination(allDestinations[2]); // Mountain Trek in City C
        cities[3].addDestination(allDestinations[3]); // Amusement Park in City D
        cities[4].addDestination(allDestinations[4]); // Local Market in City E

        return cities;
    }

    // Function to define distances (graph edges between cities)
    static vector<vector<pair<int, int>>> defineDistances(vector<City> &cities)
    {
        vector<vector<pair<int, int>>> graph(cities.size());

        // Sample roads between cities (edges with distance)
        graph[0].push_back({1, 10}); // A -> B
        graph[0].push_back({2, 15}); // A -> C
        graph[1].push_back({0, 10}); // B -> A
        graph[1].push_back({3, 20}); // B -> D
        graph[2].push_back({0, 15}); // C -> A
        graph[2].push_back({4, 30}); // C -> E
        graph[3].push_back({1, 20}); // D -> B
        graph[3].push_back({4, 25}); // D -> E
        graph[4].push_back({2, 30}); // E -> C
        graph[4].push_back({3, 25}); // E -> D
        graph[1].push_back({4, 50}); // B -> E
        graph[4].push_back({1, 50}); // E -> B

        return graph;
    }
};

// Find the shortest path between two selected cities using Dijkstra's algorithm
void findShortestRoute(int src, int dest, vector<vector<pair<int, int>>> &graph, vector<City> &cities)
{
    int n = cities.size();
    vector<int> dist(n, INT_MAX); // Initialize distances as infinity
    vector<int> parent(n, -1);    // To track the path
    dist[src] = 0;

    // Priority queue to store (distance, city)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src}); // Push the source city with distance 0

    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop(); // Always pop the smallest distance city

        int d = top.first;  // Current distance
        int u = top.second; // Current city

        // If this distance is greater than the currently recorded distance, skip
        if (d > dist[u])
        {
            continue;
        }

        for (auto &edge : graph[u])
        {
            int v = edge.first;   // Neighbor city
            int wt = edge.second; // Weight (distance) of the edge

            // Relaxation step
            if (dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
                parent[v] = u;
                pq.push({dist[v], v}); // Push the updated distance into the priority queue
            }
        }
    }

    cout << "\n\n----------------------------------------------------------\n";
    cout << "         Shortest Path Details\n";
    cout << "----------------------------------------------------------\n";
    cout << "Source City     : " << cities[src].name << endl;
    cout << "Destination City: " << cities[dest].name << endl;
    cout << "----------------------------------------------------------\n";

    if (dist[dest] == INT_MAX)
    {
        // If destination is still unreachable
        cout << "No path exists between " << cities[src].name << " and " << cities[dest].name << endl;
    }
    else
    {
        cout << "Shortest Distance: " << dist[dest] << " units\n";

        // Reconstruct and print the path
        cout << "Path: ";
        vector<int> path;
        for (int at = dest; at != -1; at = parent[at])
        {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); i++)
        {
            cout << cities[path[i]].name;
            if (i < path.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    cout << "----------------------------------------------------------\n\n\n";
}

// Optimal Travel Itinerary using 0/1 Knapsack algorithm
void optimalTravelItinerary(vector<City> &cities, int budget)
{
    cout << "\n\n----------------------------------------------------------\n";
    cout << "         Optimal Travel Itinerary (Knapsack Solution)\n";
    cout << "----------------------------------------------------------\n";
    cout << "Budget: " << budget << " units\n";

    // Collect all destinations from all cities
    vector<Destination> allDestinations;
    for (auto &city : cities)
    {
        for (auto &dest : city.destinations)
        {
            allDestinations.push_back(dest);
        }
    }

    int n = allDestinations.size();

    // DP table for 0/1 Knapsack
    vector<vector<int>> dp(n + 1, vector<int>(budget + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= budget; w++)
        {
            if (allDestinations[i - 1].cost <= w)
            {
                dp[i][w] = max(
                    allDestinations[i - 1].enjoyment + dp[i - 1][w - allDestinations[i - 1].cost],
                    dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Find which destinations are included in the optimal solution
    vector<bool> included(n, false);
    int w = budget;
    for (int i = n; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            included[i - 1] = true;
            w -= allDestinations[i - 1].cost;
        }
    }

    // Print the result
    cout << "\nSelected destinations for maximum enjoyment:\n";
    int totalCost = 0;
    int totalEnjoyment = 0;

    for (int i = 0; i < n; i++)
    {
        if (included[i])
        {
            cout << "- " << allDestinations[i].name << " (Cost: " << allDestinations[i].cost
                 << ", Enjoyment: " << allDestinations[i].enjoyment << ")\n";
            totalCost += allDestinations[i].cost;
            totalEnjoyment += allDestinations[i].enjoyment;
        }
    }

    cout << "\nTotal Cost: " << totalCost << " units\n";
    cout << "Total Enjoyment: " << totalEnjoyment << " points\n";
    cout << "----------------------------------------------------------\n\n";
}

// Floyd-Warshall algorithm to find all-pairs shortest paths
vector<vector<int>> floydWarshall(vector<vector<pair<int, int>>> &graph, int n)
{
    // Initialize distance matrix
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    // Set diagonal elements to 0
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }

    // Fill known direct distances from graph
    for (int u = 0; u < n; u++)
    {
        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;
            dist[u][v] = weight;
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

// Helper function for TSP using dynamic programming
int tspDP(int mask, int pos, int n, vector<vector<int>> &dist, vector<vector<int>> &memo)
{
    // If all cities are visited
    if (mask == (1 << n) - 1)
    {
        return dist[pos][0]; // Return to starting city
    }

    // If this state has already been calculated
    if (memo[mask][pos] != -1)
    {
        return memo[mask][pos];
    }

    int ans = INT_MAX;

    // Try to visit all unvisited cities
    for (int city = 0; city < n; city++)
    {
        if ((mask & (1 << city)) == 0)
        { // If city is not visited
            int newAns = dist[pos][city] + tspDP(mask | (1 << city), city, n, dist, memo);
            ans = min(ans, newAns);
        }
    }

    return memo[mask][pos] = ans;
}

// Find the minimum cost travel plan using TSP
void minimumCostTravelPlan(vector<City> &cities, vector<vector<pair<int, int>>> &graph)
{
    cout << "\n\n----------------------------------------------------------\n";
    cout << "         Minimum Cost Travel Plan (TSP Solution)\n";
    cout << "----------------------------------------------------------\n";

    int n = cities.size();

    // First, compute all-pairs shortest paths using Floyd-Warshall
    vector<vector<int>> dist = floydWarshall(graph, n);

    // Set up memoization table for TSP-DP
    vector<vector<int>> memo(1 << n, vector<int>(n, -1));

    // Calculate TSP starting from city 0
    int minCost = tspDP(1, 0, n, dist, memo); // Start with only city 0 visited

    cout << "The minimum cost to visit all cities (starting and ending at City "
         << cities[0].name << "): " << minCost << " units\n";

    // We can also reconstruct the path, but this is more complex
    // For simplicity, we'll just print the cost

    cout << "----------------------------------------------------------\n\n";
}

void planTrip(vector<City> &cities, vector<vector<pair<int, int>>> &graph)
{
    cout << "\nPlanning your multi-city trip...\n";
    int budget;
    cout << "Enter your travel budget: ";
    cin >> budget;

    int choice;
    cout << "\nChoose optimization strategy:\n";
    cout << "1. Maximize enjoyment within budget (Knapsack)\n";
    cout << "2. Minimize travel cost to visit all cities (TSP)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        optimalTravelItinerary(cities, budget);
    }
    else if (choice == 2)
    {
        minimumCostTravelPlan(cities, graph);
    }
    else
    {
        cout << "Invalid choice. Returning to main menu.\n";
    }
}

// Budget Management
void manageBudget()
{
    int budget, expense = 0, choice, amount;
    string desc;

    cout << "\n\n----------------------------------------------------------\n";
    cout << "              Travel Budget Management\n";
    cout << "----------------------------------------------------------\n";

    cout << "Enter your total travel budget: ";
    cin >> budget;

    vector<pair<string, int>> expenses;

    do
    {
        cout << "\n1. Add Expense\n2. View Summary\n3. Exit Budget Manager\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter expense description: ";
            cin.ignore();
            getline(cin, desc);
            cout << "Enter amount: ";
            cin >> amount;

            if (expense + amount > budget)
            {
                cout << "Warning: This expense exceeds your total budget!\n";
            }

            expense += amount;
            expenses.push_back({desc, amount});
            break;

        case 2:
            cout << "\n\n----------------------------------------------------------\n";

            cout << " Expense Summary:\n";
            cout << "----------------------------------------------------------\n\n";

            for (auto &e : expenses)
            {
                cout << "- " << e.first << " : " << e.second << " units\n";
            }
            cout << "Total Expenses : " << expense << " units\n";
            cout << "Remaining Budget : " << budget - expense << " units\n";

            cout << "\n----------------------------------------------------------\n";

            break;

        case 3:
            cout << "Exiting Budget Manager...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    cout << "----------------------------------------------------------\n\n";
}

// File handling functions
void loadUsers()
{
    ifstream file("Users.txt");
    string name, email, password;

    if (!file)
    {
        cout << "Note: Users.txt file not found. Starting with empty user database.\n";
        return;
    }

    while (file >> name >> email >> password)
    {
        users[email] = User(name, email, password);
    }

    file.close();
}

void saveUser(User &user)
{
    ofstream file("Users.txt", ios::out);

    if (!file)
    {
        cout << "Error opening Users.txt file!" << endl;
        return;
    }

    for (auto &entry : users)
    {
        file << entry.second.name << " " << entry.second.email << " " << entry.second.password << endl;
    }

    file.close();
}

// Main menu display function
void showMainMenu(User &user, vector<City> &cities, vector<vector<pair<int, int>>> &graph)
{
    int choice;
    do
    {
        cout << "=========================================================\n";
        cout << "TravelMate - Main Menu\n";
        cout << "=========================================================\n";
        cout << "1. View My Profile\n";
        cout << "2. Find Shortest Route Between Cities\n";
        cout << "3. Plan My Trip\n";
        cout << "4. View All Cities\n";
        cout << "5. View City Information\n";
        cout << "6. Update Profile\n";
        cout << "7. Logout\n";
        cout << "8. Delete My Account\n";
        cout << "9. Travel Budget Management\n";
        cout << "10. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            user.displayProfile();
            break;

        case 2:
        {
            int src, dest;
            cout << "\nAvailable cities:\n";
            for (int i = 0; i < cities.size(); i++)
            {
                cout << i << " - " << cities[i].name << endl;
            }

            cout << "\nEnter source city index (0-" << cities.size() - 1 << "): ";
            cin >> src;
            cout << "Enter destination city index (0-" << cities.size() - 1 << "): ";
            cin >> dest;
            if (src >= 0 && src < cities.size() && dest >= 0 && dest < cities.size())
            {
                findShortestRoute(src, dest, graph, cities);
            }
            else
            {
                cout << "Invalid city index. Please try again.\n";
            }
        }
        break;

        case 3:
            planTrip(cities, graph);
            break;

        case 4:
        {
            cout << "\nList of available cities:\n";
            for (int i = 0; i < cities.size(); i++)
            {
                cout << i << " - City " << cities[i].name << "\n";
                cout << "   Destinations in this city:\n";
                for (auto &dest : cities[i].destinations)
                {
                    cout << "   - " << dest.name << " (Cost: " << dest.cost
                         << ", Enjoyment: " << dest.enjoyment << ")\n";
                }
                cout << endl;
            }
        }
        break;

        case 5:
        {
            int cityIndex;
            cout << "\nEnter the city index (0-" << cities.size() - 1 << ") to view information: ";
            cin >> cityIndex;
            cout << "\n-------------------------------------------------------------------\n";
            if (cityIndex >= 0 && cityIndex < cities.size())
            {
                cout << "City Name : " << cities[cityIndex].name << endl;
                cout << "-------------------------------------------------------------------\n";

                cout << "\nAvailable Destinations:\n";
                for (auto &dest : cities[cityIndex].destinations)
                {
                    cout << "- " << dest.name << ": " << dest.description << "\n";
                    cout << "  Cost: " << dest.cost << " units, Enjoyment: " << dest.enjoyment << " points\n";
                }
                cout << "\n-------------------------------------------------------------------\n\n\n";
            }
            else
            {
                cout << "Invalid city index.\n";
            }
        }
        break;

        case 6:
        {
            string newName, newEmail, newPassword;
            cout << "\nEnter new name (or press enter to skip): ";
            getline(cin >> ws, newName);
            cout << "Enter new email (or press enter to skip): ";
            getline(cin >> ws, newEmail);
            cout << "Enter new password (or press enter to skip): ";
            getline(cin >> ws, newPassword);

            // Update profile if new details are provided
            if (!newName.empty())
                user.name = newName;
            if (!newEmail.empty())
            {
                // If email is changing, update the users map
                if (newEmail != user.email)
                {
                    users.erase(user.email);
                    user.email = newEmail;
                    users[newEmail] = user;
                }
                else
                {
                    user.email = newEmail;
                }
            }
            if (!newPassword.empty())
                user.password = newPassword;

            users[user.email] = user; // Update the user in the users map
            saveUser(user);           // Save updated profile to file
            cout << "\nProfile updated successfully!\n";
        }
        break;

        case 7:
            cout << "\nLogging out...\n";
            return; // Return to the login menu

        case 8:
        {
            char confirm;
            cout << "\nAre you sure you want to delete your account? (Y/N): ";
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                users.erase(user.email); // Remove user from the system
                // Delete from file as well
                saveUser(user);
                cout << "\nAccount deleted successfully.\n";
                return; // Return to the login menu
            }
            else
            {
                cout << "\nAccount deletion canceled.\n";
            }
        }
        break;

        case 9:
        {
            // double budget;
            // cout << "\nEnter your travel budget: ";
            // cin >> budget;

            // // Instead of just printing a suggestion, use the Knapsack algorithm
            // optimalTravelItinerary(cities, (int)budget);

            manageBudget();
            break;
        }

        break;
        case 10:
            cout << "\nExiting TravelMate. Have a great journey!\n";
            break;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 10);
}

// Sign up function
bool signup()
{
    string name, email, password;
    cout << "\n=== Sign Up ===\n";
    cout << "Enter your name : ";
    getline(cin >> ws, name);

    cout << "Enter your email: ";
    cin >> email;

    if (users.find(email) != users.end())
    {
        cout << "Account already exists! Try logging in.\n";
        return false;
    }

    cout << "Create a password: ";
    cin >> password;

    User user(name, email, password);
    users[email] = user;
    saveUser(user);

    cout << "\nSign Up successful!! Logging you in now...\n";

    vector<City> cities = City::defineCities();
    vector<vector<pair<int, int>>> graph = City::defineDistances(cities);
    showMainMenu(user, cities, graph);

    return true;
}

// Login function
User login()
{
    string email, password;
    cout << "\n=== Login ===\n";
    cout << "Email : ";
    cin >> email;
    cout << "Password : ";
    cin >> password;

    if (users.find(email) != users.end() && users[email].password == password)
    {
        cout << "\nLogin successful! Welcome, " << users[email].name << "!" << endl;
        return users[email];
    }
    else
    {
        cout << "\nInvalid email or password.\n";
        return User();
    }
}

int main()
{
    loadUsers(); // load users from file
    int choice;
    User currentUser;

    cout << endl;
    do
    {
        cout << "=========================================================\n";
        cout << "Welcome to TravelMate-The Tourist Guide Navigator\n";
        cout << "=========================================================\n";

        cout << "1. Sign Up" << endl
             << "2. Login" << endl
             << "3. Exit" << endl
             << "Choose an option: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            signup();
            break;

        case 2:
            currentUser = login();
            if (!currentUser.name.empty())
            {
                vector<City> cities = City::defineCities();
                vector<vector<pair<int, int>>> graph = City::defineDistances(cities);
                showMainMenu(currentUser, cities, graph);
            }
            break;

        case 3:
            cout << "Thank You for using TravelMate" << endl;
            break;

        default:
            cout << endl
                 << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}