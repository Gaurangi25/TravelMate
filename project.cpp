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

// Class to represent a City
class City
{
public:
    string name;
    int id;

    City(string n, int i)
    {
        name = n;
        id = i;
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
        return cities;
    }

    // Function to define distances (graph edges between cities)
    static vector<vector<pair<int, int>>> defineDistances(vector<City> &cities)
    {
        vector<vector<pair<int, int>>> graph(cities.size());

        // Sample roads between cities (edges with distance)
        graph[0].push_back({1, 10}); // A -> B
        graph[0].push_back({2, 15}); // A -> C
        graph[1].push_back({3, 20}); // B -> D
        graph[2].push_back({4, 30}); // C -> E
        graph[3].push_back({4, 25}); // D -> E
        graph[1].push_back({4, 50}); // B -> E

        return graph;
    }
};

// Find the shortest path between two selected cities.
void findShortestRoute(int src, int dest, vector<vector<pair<int, int>>> &graph, vector<City> &cities)
{
    int n = cities.size();
    vector<int> dist(n, INT_MAX); // Initialize distances as infinity
    dist[src] = 0;

    // Priority queue to store (distance, city)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src}); // Push the source city with distance 0

    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop(); // Always pop the smallest distance city

        int d = top.first; // Current distance
        int u = top.second; // Current city

        // If this distance is greater than the currently recorded distance, skip
        if (d > dist[u]) {
            continue;
        }

        for (auto &edge : graph[u])
        {
            int v = edge.first; // Neighbor city
            int wt = edge.second; // Weight (distance) of the edge

            // Relaxation step
            if (dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
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
    }

    cout << "----------------------------------------------------------\n\n\n";
}



void planTrip()
{
    cout << "\nPlanning your multi-city trip...\n";
    // Your TSP or Floyd-Warshall logic goes here
}

// File handling functions
void loadUsers()
{
    ifstream file("Users.txt");
    string name, email, password;

    if (!file)
    {
        cout << "Error opening Users.txt file!" << endl;
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
        cout << "2. Find Shortest Route\n";
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
            cout << "\nEnter source city index (0-4): ";
            cin >> src;
            cout << "Enter destination city index (0-4): ";
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
            planTrip();
            break;
        case 4:
        {
            cout << "\nList of available cities:\n";
            for (auto &city : cities)
            {
                cout << "City: " << city.name << "\n";
            }
        }
        break;
        case 5:
        {
            int cityIndex;
            cout << "\nEnter the city index (0-4) to view information: ";
            cin >> cityIndex;
            if (cityIndex >= 0 && cityIndex < cities.size())
            {
                cout << "\nCity Name: " << cities[cityIndex].name << endl;
                cout << "Information: This is a great city to visit, with many attractions and great food!\n";
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
                user.email = newEmail;
            if (!newPassword.empty())
                user.password = newPassword;

            users[user.email] = user; // Update the user in the users map
            saveUser(user); // Save updated profile to file
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
            double budget;
            cout << "\nEnter your travel budget: ";
            cin >> budget;
            cout << "Based on your budget of " << budget << " units, we suggest the following routes and cities:\n";
            // Add logic for suggesting travel based on budget
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
