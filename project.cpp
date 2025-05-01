#include <bits/stdc++.h>
using namespace std;

// Constants for file paths
const string USERS_FILE = "Users.txt";
const string TRIP_HISTORY_FILE = "TripHistory.txt";
const string REVIEWS_FILE = "Reviews.txt";
const string WEATHER_FILE = "Weather.txt";
const string USER_WISHLIST_FILE = "UserWishlist.txt"; // New file for wishlist data

// Input validation utilities
class InputValidator
{
public:
    static bool isValidEmail(const string &email)
    {
        regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(email, pattern);
    }

    static bool isValidPassword(const string &password)
    {
        return password.length() >= 6;
    }

    static int getValidInt(const string &prompt, int min, int max)
    {
        int value;
        while (true)
        {
            cout << prompt;
            if (cin >> value && value >= min && value <= max)
            {
                return value;
            }
            cout << "Value must be between " << min << " and " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    static string getValidString(const string &prompt)
    {
        string input;
        cout << prompt;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        return input;
    }
};

// Weather information for cities
class Weather
{
public:
    string city;
    string condition;
    int temperature;

    Weather() {}
    Weather(string c, string cond, int temp) : city(c), condition(cond), temperature(temp) {}

    static void initializeWeather()
    {
        vector<Weather> weatherData = {
            {"A", "Sunny", 28},
            {"B", "Rainy", 19},
            {"C", "Cloudy", 22},
            {"D", "Windy", 25},
            {"E", "Foggy", 18}};

        ofstream file(WEATHER_FILE);
        if (file.is_open())
        {
            for (const auto &w : weatherData)
            {
                file << w.city << " " << w.condition << " " << w.temperature << endl;
            }
        }
    }

    static unordered_map<string, Weather> loadWeather()
    {
        unordered_map<string, Weather> weatherMap;
        ifstream file(WEATHER_FILE);

        if (!file)
        {
            cout << "Weather data not found. Initializing...\n";
            initializeWeather();
            file.open(WEATHER_FILE);
        }

        string city, condition;
        int temp;
        while (file >> city >> condition >> temp)
        {
            weatherMap[city] = Weather(city, condition, temp);
        }

        return weatherMap;
    }
};

// Review class for destination reviews
class Review
{
public:
    string username;
    string destination;
    string comment;
    int rating; // 1-5

    Review() {}
    Review(string u, string d, string c, int r) : username(u), destination(d), comment(c), rating(r) {}

    static void saveReview(const Review &review)
    {
        ofstream file(REVIEWS_FILE, ios::app);
        if (file.is_open())
        {
            file << review.username << "|" << review.destination << "|"
                 << review.rating << "|" << review.comment << endl;
        }
    }

    static vector<Review> getReviewsForDestination(const string &dest)
    {
        vector<Review> reviews;
        ifstream file(REVIEWS_FILE);

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string username, destination, comment, ratingStr;

                getline(ss, username, '|');
                getline(ss, destination, '|');
                getline(ss, ratingStr, '|');
                getline(ss, comment);

                if (destination == dest)
                {
                    reviews.push_back(Review(username, destination, comment, stoi(ratingStr)));
                }
            }
        }
        return reviews;
    }

    static double getAverageRating(const string &dest)
    {
        vector<Review> reviews = getReviewsForDestination(dest);
        if (reviews.empty())
            return 0.0;

        double sum = 0.0;
        for (const auto &review : reviews)
        {
            sum += review.rating;
        }
        return sum / reviews.size();
    }
};

// Trip history class
class TripHistory
{
public:
    string username;
    string date;
    string itinerary;
    int cost;

    TripHistory() {}
    TripHistory(string u, string d, string i, int c) : username(u), date(d), itinerary(i), cost(c) {}

    static void saveTrip(const TripHistory &trip)
    {
        ofstream file(TRIP_HISTORY_FILE, ios::app);
        if (file.is_open())
        {
            file << trip.username << "|" << trip.date << "|"
                 << trip.itinerary << "|" << trip.cost << endl;
        }
    }

    static vector<TripHistory> getUserTrips(const string &username)
    {
        vector<TripHistory> trips;
        ifstream file(TRIP_HISTORY_FILE);

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string user, date, itinerary, costStr;

                getline(ss, user, '|');
                getline(ss, date, '|');
                getline(ss, itinerary, '|');
                getline(ss, costStr);

                if (user == username)
                {
                    trips.push_back(TripHistory(user, date, itinerary, stoi(costStr)));
                }
            }
        }
        return trips;
    }

    static string getCurrentDate()
    {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&now_time), "%Y-%m-%d");
        return ss.str();
    }
};

class User
{
public:
    string name;
    string email;
    string password;
    vector<string> wishlist;

    User() {}
    User(string n, string e, string p) : name(n), email(e), password(p) {}

    void displayProfile()
    {
        cout << "\n----------------------------\n"
             << "      User Profile\n"
             << "----------------------------\n"
             << "   Name  : " << name << endl
             << "   Email : " << email << endl
             << "----------------------------\n\n";
    }

    void addToWishlist(const string &destination)
    {
        for (const auto &item : wishlist)
        {
            if (item == destination)
            {
                cout << "This destination is already in your wishlist!\n";
                return;
            }
        }
        wishlist.push_back(destination);
        cout << destination << " added to your wishlist!\n";

        // Save wishlist to file
        saveWishlist();
    }

    void saveWishlist()
    {
        ofstream file(USER_WISHLIST_FILE, ios::app);
        if (file.is_open())
        {
            for (const auto &dest : wishlist)
            {
                file << email << "|" << dest << endl;
            }
        }
    }

    void loadWishlist()
    {
        wishlist.clear();
        ifstream file(USER_WISHLIST_FILE);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string userEmail, dest;

                getline(ss, userEmail, '|');
                getline(ss, dest);

                if (userEmail == email)
                {
                    wishlist.push_back(dest);
                }
            }
        }
    }

    void displayWishlist()
    {
        cout << "\n----------------------------\n"
             << "      Your Wishlist\n"
             << "----------------------------\n";

        if (wishlist.empty())
        {
            cout << "Your wishlist is empty.\n";
        }
        else
        {
            for (int i = 0; i < wishlist.size(); i++)
            {
                cout << (i + 1) << ". " << wishlist[i] << endl;
            }
        }
        cout << "----------------------------\n\n";
    }

    void removeFromWishlist(int index)
    {
        if (index < 1 || index > wishlist.size())
        {
            cout << "Invalid index!\n";
            return;
        }
        string removed = wishlist[index - 1];
        wishlist.erase(wishlist.begin() + index - 1);
        cout << removed << " removed from your wishlist.\n";

        // Update wishlist file after removal
        updateWishlistFile();
    }

    void updateWishlistFile()
    {
        // Get all wishlists
        ifstream infile(USER_WISHLIST_FILE);
        vector<pair<string, string>> allWishlists;
        if (infile.is_open())
        {
            string line;
            while (getline(infile, line))
            {
                stringstream ss(line);
                string userEmail, dest;

                getline(ss, userEmail, '|');
                getline(ss, dest);

                // Skip current user's entries
                if (userEmail != email)
                {
                    allWishlists.push_back({userEmail, dest});
                }
            }
            infile.close();
        }

        // Write current user's wishlist + others back to file
        ofstream outfile(USER_WISHLIST_FILE);
        if (outfile.is_open())
        {
            // Write others' wishlists
            for (const auto &item : allWishlists)
            {
                outfile << item.first << "|" << item.second << endl;
            }

            // Write current user's wishlist
            for (const auto &dest : wishlist)
            {
                outfile << email << "|" << dest << endl;
            }
            outfile.close();
        }
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
    int duration; // Duration to visit in hours

    Destination(string n, int c, int e, string desc, int d = 2) : name(n), cost(c), enjoyment(e), description(desc), duration(d) {}

    static vector<Destination> defineDestinations()
    {
        return {
            {"Museum", 20, 8, "A cultural experience with historical artifacts", 3},
            {"Beach", 10, 7, "Relax on the sandy shores", 4},
            {"Mountain Trek", 40, 10, "Challenging hike with amazing views", 6},
            {"Amusement Park", 50, 9, "Exciting rides and fun attractions", 5},
            {"Local Market", 5, 6, "Experience local culture and food", 2},
            {"Historical Monument", 15, 7, "Ancient architecture and history", 2},
            {"Wildlife Safari", 35, 9, "Experience exotic animals in their habitat", 4},
            {"Art Gallery", 18, 7, "Modern and classical art exhibitions", 2},
            {"Botanical Garden", 12, 6, "Beautiful collection of exotic plants", 3},
            {"Water Park", 40, 8, "Fun water slides and pools", 5}};
    }

    void displayReviews()
    {
        vector<Review> reviews = Review::getReviewsForDestination(name);
        double avgRating = Review::getAverageRating(name);

        cout << "\n----------------------------\n"
             << "Reviews for " << name << " (Avg: " << fixed << setprecision(1) << avgRating << "/5)\n"
             << "----------------------------\n";

        if (reviews.empty())
        {
            cout << "No reviews yet.\n";
        }
        else
        {
            for (const auto &review : reviews)
            {
                cout << "User: " << review.username << endl
                     << "Rating: " << review.rating << "/5" << endl
                     << "Comment: " << review.comment << "\n\n";
            }
        }
        cout << "----------------------------\n";
    }

    void addReview(const string &username)
    {
        cout << "Add a review for " << name << ":\n";
        int rating = InputValidator::getValidInt("Rating (1-5): ", 1, 5);

        cout << "Comment: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string comment;
        getline(cin, comment);

        Review review(username, name, comment, rating);
        Review::saveReview(review);
        cout << "Thank you for your review!\n";
    }
};

// Class to represent a City
class City
{
public:
    string name;
    int id;
    vector<Destination> destinations;
    vector<string> localCuisine;

    City(string n, int i) : name(n), id(i)
    {
        // Initialize local cuisine for each city
        if (n == "A")
        {
            localCuisine = {"Pasta", "Pizza", "Gelato"};
        }
        else if (n == "B")
        {
            localCuisine = {"Sushi", "Ramen", "Tempura"};
        }
        else if (n == "C")
        {
            localCuisine = {"Tacos", "Enchiladas", "Quesadillas"};
        }
        else if (n == "D")
        {
            localCuisine = {"Curry", "Naan", "Biryani"};
        }
        else if (n == "E")
        {
            localCuisine = {"Dim Sum", "Peking Duck", "Hot Pot"};
        }
    }

    void addDestination(const Destination &dest)
    {
        destinations.push_back(dest);
    }

    static vector<City> defineCities()
    {
        vector<City> cities = {
            {"A", 0}, {"B", 1}, {"C", 2}, {"D", 3}, {"E", 4}};

        vector<Destination> allDestinations = Destination::defineDestinations();

        // Add destinations to cities
        cities[0].addDestination(allDestinations[0]);
        cities[0].addDestination(allDestinations[5]);
        cities[1].addDestination(allDestinations[1]);
        cities[1].addDestination(allDestinations[9]);
        cities[2].addDestination(allDestinations[2]);
        cities[2].addDestination(allDestinations[6]);
        cities[3].addDestination(allDestinations[3]);
        cities[3].addDestination(allDestinations[7]);
        cities[4].addDestination(allDestinations[4]);
        cities[4].addDestination(allDestinations[8]);

        return cities;
    }

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

    void displayLocalCuisine()
    {
        cout << "\n----------------------------\n"
             << "Local Cuisine in City " << name << "\n"
             << "----------------------------\n";
        for (const auto &dish : localCuisine)
        {
            cout << "- " << dish << endl;
        }
        cout << "----------------------------\n";
    }

    void displayWeather(const unordered_map<string, Weather> &weatherMap)
    {
        if (weatherMap.find(name) != weatherMap.end())
        {
            const Weather &weather = weatherMap.at(name);
            cout << "\n----------------------------\n"
                 << "Weather in City " << name << "\n"
                 << "----------------------------\n"
                 << "Condition: " << weather.condition << endl
                 << "Temperature: " << weather.temperature << "°C" << endl
                 << "----------------------------\n";
        }
        else
        {
            cout << "Weather information not available for City " << name << endl;
        }
    }
};

// Class to represent team members
class TripGroup
{
public:
    vector<string> members;
    unordered_map<string, int> paid;
    int totalExpense = 0;

    void addMember(const string &name)
    {
        members.push_back(name);
        paid[name] = 0;
    }

    void addExpense(const string &expenseName, int amount, int payerIndex)
    {
        if (payerIndex >= 0 && payerIndex < members.size())
        {
            string payer = members[payerIndex];
            paid[payer] += amount;
            totalExpense += amount;
            cout << "Expense added: " << expenseName << " | Amount: " << amount
                 << " | Paid by: " << payer << endl;
        }
        else
        {
            cout << "Invalid payer index.\n";
        }
    }

    void calculateShares()
    {
        cout << "\n-------- Expense Split Summary --------\n";
        int perPersonShare = totalExpense / members.size();

        for (const string &member : members)
        {
            int balance = paid[member] - perPersonShare;
            if (balance > 0)
                cout << member << " is owed " << balance << " units.\n";
            else if (balance < 0)
                cout << member << " owes " << -balance << " units.\n";
            else
                cout << member << " is settled.\n";
        }
        cout << "----------------------------------------\n";
    }

    void calculateDetailedTransactions()
    {
        cout << "\n-------- Detailed Transaction Plan --------\n";
        int perPersonShare = totalExpense / members.size();

        // Calculate net balances
        vector<pair<string, int>> balances;
        for (const string &member : members)
        {
            int balance = paid[member] - perPersonShare;
            balances.push_back({member, balance});
        }

        // Sort by balance (descending)
        sort(balances.begin(), balances.end(),
             [](const pair<string, int> &a, const pair<string, int> &b)
             {
                 return a.second > b.second;
             });

        // Generate transactions
        int i = 0;                   // index for creditors (positive balance)
        int j = balances.size() - 1; // index for debtors (negative balance)

        while (i < j)
        {
            string creditor = balances[i].first;
            string debtor = balances[j].first;
            int creditorAmount = balances[i].second;
            int debtorAmount = -balances[j].second;

            if (creditorAmount == 0)
            {
                i++;
                continue;
            }

            if (debtorAmount == 0)
            {
                j--;
                continue;
            }

            int transferAmount = min(creditorAmount, debtorAmount);
            cout << debtor << " pays " << creditor << " " << transferAmount << " units.\n";

            balances[i].second -= transferAmount;
            balances[j].second += transferAmount;

            if (balances[i].second == 0)
                i++;
            if (balances[j].second == 0)
                j--;
        }
        cout << "----------------------------------------\n";
    }
};

// Find the shortest path between two selected cities using Dijkstra's algorithm
void findShortestRoute(int src, int dest, vector<vector<pair<int, int>>> &graph, vector<City> &cities)
{
    int n = cities.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int wt = edge.second;

            if (dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\n\n----------------------------------------------------------\n"
         << "         Shortest Path Details\n"
         << "----------------------------------------------------------\n"
         << "Source City     : " << cities[src].name << endl
         << "Destination City: " << cities[dest].name << endl
         << "----------------------------------------------------------\n";

    if (dist[dest] == INT_MAX)
    {
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
                cout << " -> ";
        }
        cout << endl;

        // Calculate travel cost estimation
        cout << "\nEstimated Travel Cost:" << endl;
        int totalDistance = dist[dest];
        int fuelCost = totalDistance * 0.5;
        int tollCharges = path.size() * 5;
        cout << "- Fuel cost (0.5 units/distance): " << fuelCost << " units" << endl
             << "- Toll charges: " << tollCharges << " units" << endl
             << "Total estimated travel cost: " << (fuelCost + tollCharges) << " units" << endl;
    }
    cout << "----------------------------------------------------------\n\n\n";
}

// Optimal Travel Itinerary using 0/1 Knapsack algorithm
void optimalTravelItinerary(vector<City> &cities, int budget, const string &username = "")
{
    cout << "\n\n----------------------------------------------------------\n"
         << "         Optimal Travel Itinerary (Knapsack Solution)\n"
         << "----------------------------------------------------------\n"
         << "Budget: " << budget << " units\n";

    // Collect all destinations from all cities
    vector<Destination> allDestinations;
    unordered_map<int, pair<string, string>> destInfo;
    int index = 0;

    for (auto &city : cities)
    {
        for (auto &dest : city.destinations)
        {
            allDestinations.push_back(dest);
            destInfo[index++] = {city.name, dest.name};
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
    int totalDuration = 0;
    string itinerary;

    for (int i = 0; i < n; i++)
    {
        if (included[i])
        {
            cout << "- " << destInfo[i].first << ": " << allDestinations[i].name
                 << " (Cost: " << allDestinations[i].cost
                 << ", Enjoyment: " << allDestinations[i].enjoyment
                 << ", Duration: " << allDestinations[i].duration << "h)\n";

            totalCost += allDestinations[i].cost;
            totalEnjoyment += allDestinations[i].enjoyment;
            totalDuration += allDestinations[i].duration;

            if (!itinerary.empty())
                itinerary += " -> ";
            itinerary += destInfo[i].first + ":" + allDestinations[i].name;
        }
    }

    cout << "\nTotal Cost: " << totalCost << " units\n"
         << "Total Enjoyment: " << totalEnjoyment << " points\n"
         << "Total Duration: " << totalDuration << " hours\n";

    // Save trip to history if username is provided
    if (!username.empty())
    {
        char saveChoice;
        cout << "\nDo you want to save this itinerary to your trip history? (Y/N): ";
        cin >> saveChoice;

        if (saveChoice == 'Y' || saveChoice == 'y')
        {
            TripHistory trip(username, TripHistory::getCurrentDate(), itinerary, totalCost);
            TripHistory::saveTrip(trip);
            cout << "\nTrip saved to your history!\n";
        }
    }
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
            dist[u][edge.first] = edge.second;
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // Avoid integer overflow
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
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
            if (newAns >= 0)
            { // Prevent integer overflow
                ans = min(ans, newAns);
            }
        }
    }
    return memo[mask][pos] = ans;
}

// Find the minimum cost travel plan using TSP
void minimumCostTravelPlan(vector<City> &cities, vector<vector<pair<int, int>>> &graph)
{
    cout << "\n\n----------------------------------------------------------\n"
         << "         Minimum Cost Travel Plan (TSP Solution)\n"
         << "----------------------------------------------------------\n";

    int n = cities.size();

    // First, compute all-pairs shortest paths using Floyd-Warshall
    vector<vector<int>> dist = floydWarshall(graph, n);

    // Set up memoization table for TSP-DP
    vector<vector<int>> memo(1 << n, vector<int>(n, -1));

    // Calculate TSP starting from city 0
    int minCost = tspDP(1, 0, n, dist, memo); // Start with only city 0 visited

    cout << "The minimum cost to visit all cities (starting and ending at City "
         << cities[0].name << "): " << minCost << " units\n"
         << "----------------------------------------------------------\n\n";
}

void planTrip(vector<City> &cities, vector<vector<pair<int, int>>> &graph, const string &username = "")
{
    cout << "\nPlanning your multi-city trip...\n";
    int budget;
    cout << "Enter your travel budget: ";
    cin >> budget;

    int choice;
    cout << "\nChoose optimization strategy:\n"
         << "1. Maximize enjoyment within budget (Knapsack)\n"
         << "2. Minimize travel cost to visit all cities (TSP)\n"
         << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        optimalTravelItinerary(cities, budget, username);
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
    vector<pair<string, int>> expenses;

    cout << "\n\n----------------------------------------------------------\n"
         << "              Travel Budget Management\n"
         << "----------------------------------------------------------\n"
         << "Enter your total travel budget: ";
    cin >> budget;

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
            cout << "\n\n----------------------------------------------------------\n"
                 << " Expense Summary:\n"
                 << "----------------------------------------------------------\n\n";

            for (auto &e : expenses)
            {
                cout << "- " << e.first << " : " << e.second << " units\n";
            }
            cout << "Total Expenses : " << expense << " units\n"
                 << "Remaining Budget : " << budget - expense << " units\n"
                 << "\n----------------------------------------------------------\n";
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
        cout << "6. Group Expense Split (Splitwise)\n";
        cout << "7. Travel Budget Management\n";
        cout << "8. Update Profile\n";
        cout << "9. Logout\n";
        cout << "10. Delete My Account\n";
        cout << "11. Exit\n";

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
            TripGroup group;
            int numMembers;
            cout << "\nEnter number of travelers in the group: ";
            cin >> numMembers;

            cin.ignore(); // Clear newline buffer
            for (int i = 0; i < numMembers; ++i)
            {
                string name;
                cout << "Enter name of traveler " << (i + 1) << ": ";
                getline(cin, name);
                group.addMember(name);
            }

            int addMore;
            do
            {
                string expenseName;
                int amount, payerIndex;

                cout << "\nEnter expense name: ";
                getline(cin, expenseName);
                cout << "Enter amount: ";
                cin >> amount;

                cout << "Who paid for this? Select index:\n";
                for (int i = 0; i < group.members.size(); ++i)
                    cout << i << " - " << group.members[i] << endl;
                cout << "Enter payer index: ";
                cin >> payerIndex;
                cin.ignore();

                group.addExpense(expenseName, amount, payerIndex);

                cout << "Do you want to add another expense? (1 = Yes, 0 = No): ";
                cin >> addMore;
                cin.ignore();
            } while (addMore == 1);

            group.calculateShares();
        }
        break;

        case 7:
        {
            // double budget;
            // cout << "\nEnter your travel budget: ";
            // cin >> budget;

            // // Instead of just printing a suggestion, use the Knapsack algorithm
            // optimalTravelItinerary(cities, (int)budget);

            manageBudget();
            break;
        }

        case 8:
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

        case 9:
            cout << "\nLogging out...\n";
            return; // Return to the login menu

        case 10:
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

        case 11:
            cout << "\nExiting TravelMate. Have a great journey!\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 11);
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