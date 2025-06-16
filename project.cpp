#include <bits/stdc++.h>
#include <fstream>
using namespace std;
//users.text

class User{
    public:
    string name;
    string email;
    string password;
    User() {}
    User(string n, string e, string p) : name(n), email(e), password(p) {}

    void displayProfile() {
        cout << "\n----------------------------\n"
             << "      User Profile\n"
             << "----------------------------\n"
             << "   Name  : " << name << endl
             << "   Email : " << email << endl
             << "----------------------------\n\n";
    }
};

unordered_map<string, User> users;

class Destination{
public:
    string name;
    int cost;      // Cost to visit this destination
    int enjoyment; // Enjoyment value of this destination
    string description; // about the place
    int duration;  // Duration to visit in hours

};
class City{
public:
    string name;
    int id;
    string weather;
    vector<Destination> destinations;  //places to visit in a city

};
using CityGraph = vector<vector<pair<int, int>>>; // Adjacency list

unordered_map<int, City> createCitiesData() {
    unordered_map<int, City> cities;

    cities[0] = {"Delhi", 0, "Hot in summer, cold in winter", {
        {"Red Fort", 500, 8, "Historic fort and UNESCO site.", 2},
        {"India Gate", 0, 7, "War memorial and picnic spot.", 1},
        {"Qutub Minar", 300, 8, "UNESCO world heritage site.", 2},
        {"Lotus Temple", 0, 7, "Bahá'í House of Worship with unique architecture.", 1},
        {"Humayun's Tomb", 250, 8, "Mughal garden-tomb, UNESCO site.", 2}
    }};

    cities[1] = {"Mumbai", 1, "Humid and coastal", {
        {"Gateway of India", 0, 7, "Iconic arch by the sea.", 1},
        {"Marine Drive", 0, 9, "Scenic seaside road.", 2},
        {"Elephanta Caves", 200, 8, "Ancient rock-cut temples.", 3},
        {"Siddhivinayak Temple", 0, 8, "Famous Ganesha temple.", 1},
        {"Chhatrapati Shivaji Maharaj Terminus", 0, 8, "Gothic-style railway station.", 2}
    }};

    cities[2] = {"Jaipur", 2, "Hot and dry", {
        {"Hawa Mahal", 100, 8, "Palace with lattice windows.", 1},
        {"Amber Fort", 400, 9, "Historic fort on a hill.", 3},
        {"City Palace", 200, 7, "Royal residence and museum.", 2},
        {"Jantar Mantar", 50, 8, "Astronomical instruments and UNESCO site.", 2},
        {"Nahargarh Fort", 100, 7, "Offers panoramic city views.", 2}
    }};

    cities[3] = {"Agra", 3, "Hot in summer, mild in winter", {
        {"Taj Mahal", 50, 10, "World-famous white marble mausoleum.", 3},
        {"Agra Fort", 40, 8, "Historic fort and UNESCO site.", 2},
        {"Mehtab Bagh", 20, 7, "Garden with a great Taj Mahal view.", 1},
        {"Fatehpur Sikri", 40, 8, "Historic Mughal capital and UNESCO site.", 3},
        {"Itimad-ud-Daulah", 25, 7, "Known as 'Baby Taj'.", 2}
    }};

    cities[4] = {"Kolkata", 4, "Humid and tropical", {
        {"Victoria Memorial", 30, 8, "Museum and memorial in colonial style.", 2},
        {"Howrah Bridge", 0, 7, "Iconic cantilever bridge.", 1},
        {"Indian Museum", 50, 8, "Oldest and largest museum in India.", 2},
        {"Kalighat Temple", 0, 8, "One of the 51 Shakti Peethas.", 1},
        {"Science City", 60, 7, "Interactive science museum.", 2}
    }};

    cities[5] = {"Bengaluru", 5, "Moderate climate", {
        {"Lalbagh Botanical Garden", 20, 7, "Expansive garden with rare plants.", 2},
        {"Bangalore Palace", 230, 8, "Palace inspired by Windsor Castle.", 2},
        {"Cubbon Park", 0, 7, "Green park in the city center.", 1},
        {"Vidhana Soudha", 0, 8, "Imposing legislative building.", 1},
        {"Bannerghatta Biological Park", 100, 8, "Safari and wildlife reserve.", 3}
    }};

    cities[6] = {"Hyderabad", 6, "Hot and dry", {
        {"Charminar", 20, 8, "Historic monument with four minarets.", 1},
        {"Golconda Fort", 80, 9, "Ruins of a fort with acoustic marvels.", 3},
        {"Ramoji Film City", 1150, 9, "World’s largest film studio complex.", 4},
        {"Hussain Sagar Lake", 0, 7, "Lake with a large Buddha statue.", 2},
        {"Salar Jung Museum", 50, 8, "Major museum with global art collections.", 2}
    }};

    cities[7] = {"Udaipur", 7, "Pleasant and dry", {
        {"City Palace", 300, 9, "Palace complex with great views.", 2},
        {"Lake Pichola", 0, 8, "Beautiful lake with boat rides.", 2},
        {"Sajjangarh Fort", 100, 7, "Hilltop fort with sunset views.", 2},
        {"Jag Mandir", 50, 8, "Island palace in Lake Pichola.", 2},
        {"Bagore Ki Haveli", 60, 7, "Museum with traditional performances.", 2}
    }};

    cities[8] = {"Varanasi", 8, "Hot and humid", {
        {"Kashi Vishwanath Temple", 0, 9, "One of the holiest temples for Hindus.", 1},
        {"Dashashwamedh Ghat", 0, 8, "Famous for Ganga Aarti.", 1},
        {"Sarnath", 20, 8, "Buddhist site where Buddha gave his first sermon.", 2},
        {"Manikarnika Ghat", 0, 7, "Sacred cremation ghat.", 1},
        {"Ramnagar Fort", 40, 7, "18th-century fort and museum.", 2}
    }};

    cities[9] = {"Amritsar", 9, "Extreme temperatures", {
        {"Golden Temple", 0, 10, "Spiritual center of Sikhism.", 2},
        {"Jallianwala Bagh", 0, 8, "Memorial of tragic massacre.", 1},
        {"Wagah Border", 0, 9, "Daily flag-lowering ceremony.", 2},
        {"Partition Museum", 20, 8, "Dedicated to the 1947 Partition.", 2},
        {"Durgiana Temple", 10, 7, "Similar architecture to Golden Temple.", 1}
    }};

    cities[10] = {"Chennai", 10, "Hot and humid", {
        {"Marina Beach", 0, 7, "One of the longest urban beaches.", 2},
        {"Kapaleeshwarar Temple", 0, 8, "Historic Dravidian-style temple.", 1},
        {"Fort St. George", 15, 7, "Colonial fort and museum.", 2},
        {"Santhome Cathedral", 0, 7, "Tomb of St. Thomas the Apostle.", 1},
        {"Guindy National Park", 30, 8, "Wildlife park in the city.", 2}
    }};

    cities[11] = {"Mysuru", 11, "Pleasant climate", {
        {"Mysore Palace", 100, 9, "Royal heritage palace.", 2},
        {"Chamundi Hill", 0, 8, "Temple and panoramic views.", 2},
        {"Brindavan Gardens", 50, 8, "Famous for musical fountain show.", 2},
        {"St. Philomena’s Church", 0, 7, "Neo-Gothic church.", 1},
        {"Railway Museum", 30, 7, "Showcases heritage locomotives.", 2}
    }};

    cities[12] = {"Pune", 12, "Moderate climate", {
        {"Shaniwar Wada", 25, 7, "Historic fortification.", 2},
        {"Aga Khan Palace", 20, 8, "Important site in India's freedom movement.", 1},
        {"Sinhagad Fort", 30, 8, "Trekking destination with historical significance.", 3},
        {"Rajiv Gandhi Zoo", 40, 7, "Popular wildlife spot.", 2},
        {"Parvati Hill", 10, 7, "Hilltop temples and view.", 1}
    }};

    cities[13] = {"Goa", 13, "Tropical and humid", {
        {"Baga Beach", 0, 9, "Popular beach with nightlife.", 2},
        {"Fort Aguada", 0, 8, "Well-preserved 17th-century fort.", 1},
        {"Basilica of Bom Jesus", 0, 9, "UNESCO site with preserved remains of St. Francis Xavier.", 1},
        {"Dudhsagar Falls", 400, 9, "Majestic waterfall in the Western Ghats.", 4},
        {"Anjuna Flea Market", 0, 7, "Vibrant local market.", 1}
    }};

    cities[14] = {"Rishikesh", 14, "Pleasant and spiritual", {
        {"Lakshman Jhula", 0, 7, "Iconic suspension bridge.", 1},
        {"Triveni Ghat", 0, 8, "Sacred ghat for Ganga Aarti.", 1},
        {"Beatles Ashram", 150, 8, "Meditation site popularized by The Beatles.", 2},
        {"Neelkanth Mahadev Temple", 30, 8, "Lord Shiva temple in the hills.", 2},
        {"Parmarth Niketan", 0, 7, "Yoga and spiritual center.", 1}
    }};

    cities[15] = {"Darjeeling", 15, "Cool and pleasant", {
        {"Tiger Hill", 0, 9, "Sunrise viewpoint for Kanchenjunga.", 1},
        {"Darjeeling Himalayan Railway", 100, 8, "UNESCO-listed toy train ride.", 3},
        {"Batasia Loop", 15, 7, "Beautiful railway loop with garden.", 1},
        {"Peace Pagoda", 0, 8, "Buddhist stupa with mountain views.", 1},
        {"Happy Valley Tea Estate", 50, 8, "Tea plantation with factory tours.", 2}
    }};

    return cities;
}

// for given city and given budget find max enjoyment and print
int knapsackRecursive(const vector<Destination>& destinations, int n, int budget) {
    // Base case: If no more destinations or no remaining budget
    if (n == 0 || budget == 0)
        return 0;

    if (destinations[n - 1].cost > budget)  //n-1 bcs destinaton is 0 based
        return knapsackRecursive(destinations, n - 1, budget);

    int exclude = knapsackRecursive(destinations, n - 1, budget);
    int include = destinations[n - 1].enjoyment + knapsackRecursive(destinations, n - 1, budget - destinations[n - 1].cost);

    return max(exclude, include);
}

void printSelectedDestinations(const vector<Destination>& destinations, int n, int budget) {
    int maxEnjoyment = knapsackRecursive(destinations, n, budget);

    cout << "Maximum enjoyment: " << maxEnjoyment << endl;
    cout << "Places to visit within the budget:" << endl;
    vector<pair<string,int>> places;

    // Backtracking
    while (n > 0 && budget > 0) {
        if (knapsackRecursive(destinations, n - 1, budget) != maxEnjoyment) {
            // destination included
            places.push_back({destinations[n - 1].name,destinations[n - 1].cost});
            budget -= destinations[n - 1].cost;
            maxEnjoyment -= destinations[n - 1].enjoyment;
        }
        n--;
    }

    for (int i = places.size() - 1; i >= 0; --i) {
        cout << "- " << places[i].first <<" in "<<places[i].second<<"rupees"<< endl;
    }
}

vector<vector<pair<int, int>>> createCityGraph() {

    vector<vector<pair<int, int>>> graph(16); // Adjust size based on number of cities

    // Delhi (0)
    graph[0].push_back({1, 1400});  // Mumbai
    graph[0].push_back({2, 280});   // Jaipur
    graph[0].push_back({3, 230});   // Agra
    graph[0].push_back({4, 1500});  // Kolkata
    graph[0].push_back({5, 2150});  // Bengaluru
    graph[0].push_back({6, 1580});  // Hyderabad
    graph[0].push_back({8, 820});   // Varanasi
    graph[0].push_back({9, 450});   // Amritsar
    graph[0].push_back({10, 2200}); // Chennai

    // Mumbai (1)
    graph[1].push_back({0, 1400});  // Delhi
    graph[1].push_back({2, 1140});  // Jaipur
    graph[1].push_back({4, 2000});  // Kolkata
    graph[1].push_back({5, 980});   // Bengaluru
    graph[1].push_back({6, 710});   // Hyderabad
    graph[1].push_back({10, 1330}); // Chennai
    graph[1].push_back({12, 150});  // Pune
    graph[1].push_back({13, 590});  // Goa

    // Jaipur (2)
    graph[2].push_back({0, 280});   // Delhi
    graph[2].push_back({1, 1140});  // Mumbai
    graph[2].push_back({3, 240});   // Agra
    graph[2].push_back({7, 390});   // Udaipur

    // Agra (3)
    graph[3].push_back({0, 230});   // Delhi
    graph[3].push_back({2, 240});   // Jaipur
    graph[3].push_back({8, 610});   // Varanasi

    // Kolkata (4)
    graph[4].push_back({0, 1500});  // Delhi
    graph[4].push_back({1, 2000});  // Mumbai
    graph[4].push_back({6, 1500});  // Hyderabad
    graph[4].push_back({10, 1670}); // Chennai
    graph[4].push_back({15, 620});  // Darjeeling

    // Bengaluru (5)
    graph[5].push_back({0, 2150});  // Delhi
    graph[5].push_back({1, 980});   // Mumbai
    graph[5].push_back({6, 570});   // Hyderabad
    graph[5].push_back({10, 350});  // Chennai
    graph[5].push_back({11, 150});  // Mysuru
    graph[5].push_back({12, 840});  // Pune

    // Hyderabad (6)
    graph[6].push_back({0, 1580});  // Delhi
    graph[6].push_back({1, 710});   // Mumbai
    graph[6].push_back({4, 1500});  // Kolkata
    graph[6].push_back({5, 570});   // Bengaluru
    graph[6].push_back({10, 630});  // Chennai

    // Udaipur (7)
    graph[7].push_back({2, 390});   // Jaipur
    graph[7].push_back({13, 640});  // Goa

    // Varanasi (8)
    graph[8].push_back({0, 820});   // Delhi
    graph[8].push_back({3, 610});   // Agra
    graph[8].push_back({4, 680});   // Kolkata

    // Amritsar (9)
    graph[9].push_back({0, 450});   // Delhi

    // Chennai (10)
    graph[10].push_back({1, 1330}); // Mumbai
    graph[10].push_back({4, 1670}); // Kolkata
    graph[10].push_back({5, 350});  // Bengaluru
    graph[10].push_back({6, 630});  // Hyderabad

    // Mysuru (11)
    graph[11].push_back({5, 150});  // Bengaluru

    // Pune (12)
    graph[12].push_back({1, 150});  // Mumbai
    graph[12].push_back({5, 840});  // Bengaluru

    // Goa (13)
    graph[13].push_back({1, 590});  // Mumbai
    graph[13].push_back({7, 640});  // Udaipur

    // Rishikesh (14)
    graph[14].push_back({0, 240});  // Delhi

    // Darjeeling (15)
    graph[15].push_back({4, 620});  // Kolkata

    return graph;
}

const int INF = 1e9;
const int N = 16; // Total number of cities
vector<string> cityNames = {
    "Delhi", "Mumbai", "Jaipur", "Agra", "Kolkata", "Bengaluru", "Hyderabad",
    "Udaipur", "Varanasi", "Amritsar", "Chennai", "Mysuru", "Pune", "Goa",
    "Rishikesh", "Darjeeling"
};

void dijkstra(int src, int dest,vector<vector<pair<int, int>>>graph) {
    vector<int> dist(N, INF);
    vector<int> parent(N, -1); // To store path
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [curDist, u] = pq.top();
        pq.pop();

        for (auto [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u; // Track the path
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No path between " << cityNames[src] << " and " << cityNames[dest] << "\n";
        return;
    }

    // Reconstruct the path
    vector<int> path;
    for (int at = dest; at != -1; at = parent[at])
        path.push_back(at);

    reverse(path.begin(), path.end());

    // Output
    cout << "Shortest distance from " << cityNames[src] << " to " << cityNames[dest] << " is: " << dist[dest] << " km\n";
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << cityNames[path[i]];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n";
}

void floydWarshallWithSource(int src ,vector<vector<pair<int, int>>>graph){
    vector<vector<int>> dist(N, vector<int>(N, INF));
    vector<vector<int>> nextCity(N, vector<int>(N, -1));  // To keep track of the next city for the shortest path

    // Initialize distances with direct edges from the graph
    for (int u = 0; u < N; ++u) {
        dist[u][u] = 0;  // Distance to itself is 0
        for (auto &[v, weight] : graph[u]) {
            dist[u][v] = weight;  // Direct distance from u to v
            nextCity[u][v] = v;   // Set next city for path reconstruction
        }
    }

    // Step 2: Floyd-Warshall algorithm (all-pairs shortest path)
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];  // Update the distance
                    nextCity[i][j] = nextCity[i][k];      // Update next city for path reconstruction
                }
            }
        }
    }

    // Step 3: Print the shortest distance from the source city to all other cities
    cout << "Shortest distances from " << cityNames[src] << ":\n";
    for (int dest = 0; dest < N; ++dest) {
        if (dist[src][dest] == INF) {
            cout << "No path from " << cityNames[src] << " to " << cityNames[dest] << "\n";
        } else {
            cout << "Distance from " << cityNames[src] << " to " << cityNames[dest] << ": " << dist[src][dest] << " km\n";
        }
    }
}

void loadUsers(){
    fstream file;
    file.open("Users.txt", ios::in | ios::out);
    string name, email, password;
    if (!file.is_open())
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

void saveUser(User &user){
    fstream file;
    file.open("Users.txt", ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening Users.txt file!" << endl;
        return;
    }
    file << user.name << " " << user.email << " " << user.password << endl;
    file.close();
    cout << "User appended to file successfully." << endl;
}

bool signup(string &mail){
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
    mail=email;

    cout << "\nSign Up successful!! Logging you in now...\n";

    return true;
}

bool login(string & mail){
    string email, password;
    cout << "\n=== Login ===\n";
    cout << "Email : ";
    cin >> email;
    cout << "Password : ";
    cin >> password;
    if (users.find(email) != users.end() && users[email].password == password)
    {
        cout << "\nLogin successful! Welcome, " << users[email].name << "!" << endl;
        mail=email;
        return true;
    }
    else
    {
        cout << "\nInvalid email or password.\n";
        return false;
    }
}

void printMenu(){
        cout << "=========================================================\n";
        cout << "TravelMate - Main Menu\n";
        cout << "=========================================================\n";
        cout << "1. View My Profile\n";
        cout << "2. Path and cost to visit a city\n";
        cout << "3. Plan My Trip\n";
        cout << "4. View All Cities\n";
        cout << "5. View City Information\n";
        cout << "6. View minimum distance of all cities\n";
        cout << "7. Travel Budget Management\n";
        cout << "8. Group Expense Split (Splitwise)\n";
        cout << "9. Exit\n";

}

void disAndPath(unordered_map<int,City> cities, vector<vector<pair<int, int>>> graph){
        int src, dest;
        cout << "\nAvailable cities:\n";
        for (int i = 0; i < N; i++)
        {
            cout << i << " - " << cities[i].name << endl;
        }
        cout << "\nEnter Current city index (0-" << N- 1 << "): ";
        cin >> src;
        cout << "Enter destination city index (0-" << N- 1 << "): ";
        cin >> dest;
        if ((src >= 0 && src < N) && dest >= 0 && dest < N){
            dijkstra(src, dest, graph);
        }else{
            cout << "Invalid city index. Please try again.\n";
        }
}

void printCities(unordered_map<int,City> cities){
       cout << "\nList of available cities:\n";
        for (int i = 0; i < cities.size(); i++)
        {
            cout << i << " - City " << cities[i].name << "\n";
            cout << endl;
        }
}

void cityInformation(unordered_map<int,City> cities){
       printCities(cities);
       int cityIndex;
        cout << "\nEnter the city index (0-" << N-1 << ") to view information: ";
        cin >> cityIndex;
        cout << "\n-------------------------------------------------------------------\n";
        if (cityIndex >= 0 && cityIndex < N)
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

void allCityDistance(unordered_map<int,City> cities, vector<vector<pair<int, int>>> graph){
    int src;
    printCities(cities);
    cout<<"\nEnter your current city index";
    cin>>src;
    floydWarshallWithSource(src,graph);

}

void budgetManagement(unordered_map<int,City> cities){
     int index,budget;
     printCities(cities);

     cout<<"\nEnter the city index you want to visit: ";
     cin>>index;
     cout<<"\nEnter your budget";
     cin>>budget;
     vector<Destination> places=cities[index].destinations;
     int n= places.size();
     printSelectedDestinations(places,n,budget);

}
class Splitwise {
    public:

    string name;
    vector<string> members;
    unordered_map<string, unordered_map<string, double>> balance;

    void addMember(const string& name) {
        members.push_back(name);
    }

    void addExpense(const string& paidBy, double amount, const vector<string>& splitBetween) {
        int numPeople = splitBetween.size();
        double splitAmount = amount / numPeople;

        for (const string& person : splitBetween) {
            if (person == paidBy) continue;
            balance[person][paidBy] += splitAmount;
            balance[paidBy][person] -= splitAmount;
        }
    }

    void showBalances() {
        cout << fixed << setprecision(2);
        cout << "\nFinal Balances:\n";
        for (const string& a : members) {
            for (const string& b : members) {
                if (balance[a][b] > 0.01) {
                    cout << a << " owes " << b << " " << balance[a][b] <<" rupees"<< endl;
                }
            }
        }
    }
};
void splitExpenses() {
    Splitwise s;
    int num;
    cout << "\nEnter Group name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "\nEnter number of members: ";
    cin >> num;
    string member;
    for (int i = 1; i <= num; i++) {
        cout << "Enter member name " << i << ": ";
        cin >> member;
        s.addMember(member);
    }

    cout << "\nEnter number of expenses: ";
    cin >> num;

    for (int i = 1; i <= num; i++) {
        string paidby;
        double amount;
        int numSplit;
        cout << "\nExpense " << i << ":\n";
        cout << "Paid by: ";
        cin >> paidby;
        cout << "Amount: ";
        cin >> amount;
        cout << "Number of people involved in this expense: ";
        cin >> numSplit;

        vector<string> splitBetween;
        cout << "Enter names of people to split between:\n";
        for (int j = 1; j <= numSplit; j++) {
            string name;
            cin >> name;
            splitBetween.push_back(name);
        }

        s.addExpense(paidby, amount, splitBetween);
    }

    s.showBalances();
}



// Recursive TSP with path tracking
int tsp(int mask, int pos, const vector<vector<int>>& dist, vector<vector<int>>& dp,
        vector<vector<int>>& parent, int start, int total) {
    if (mask == (1 << total) - 1)
        return dist[pos][start];  // All cities visited, return to start

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int next = 0; next < total; ++next) {
        if (!(mask & (1 << next))) {
            int newMask = mask | (1 << next);
            int cost = dist[pos][next] + tsp(newMask, next, dist, dp, parent, start, total);
            if (cost < ans) {
                ans = cost;
                parent[mask][pos] = next;
            }
        }
    }
    return dp[mask][pos] = ans;
}

void printPath(int mask, int pos, const vector<vector<int>>& parent,
               const vector<int>& citiesToVisit, int start) {
    cout << "\nOptimal Path:\n";
    cout << citiesToVisit[pos] << " -> ";
    while (mask != (1 << citiesToVisit.size()) - 1) {
        int next = parent[mask][pos];
        cout << citiesToVisit[next] << " -> ";
        mask |= (1 << next);
        pos = next;
    }
    cout << citiesToVisit[start] << endl; // return to start
}

void customized_TSP(unordered_map<int,City> cities,const vector<vector<pair<int, int>>>& graph) {
    int num;
    cout << "Enter number of cities to visit (<= 16): ";
    cin >> num;
    printCities(cities);
    vector<int> citiesToVisit;
    cout << "Enter city IDs to visit (space-separated): ";
    for (int i = 0; i < num; ++i) {
        int id;
        cin >> id;
        citiesToVisit.push_back(id);
    }

    int startCity;
    cout << "Enter starting city ID: ";
    cin >> startCity;

    // Ensure startCity is in the list
    if (find(citiesToVisit.begin(), citiesToVisit.end(), startCity) == citiesToVisit.end()) {
        citiesToVisit.insert(citiesToVisit.begin(), startCity);
    }

    int k = citiesToVisit.size();

    // Floyd-Warshall to compute all-pairs shortest path
    vector<vector<int>> dist(N, vector<int>(N, INF));
    for (int i = 0; i < N; ++i) dist[i][i] = 0;
    for (int u = 0; u < N; ++u)
        for (auto [v, cost] : graph[u])
            dist[u][v] = min(dist[u][v], cost);

    for (int m = 0; m < N; ++m)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dist[i][j] = min(dist[i][j], dist[i][m] + dist[m][j]);

    // Reduced distance matrix for chosen cities
    vector<vector<int>> reduced(k, vector<int>(k));
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j)
            reduced[i][j] = dist[citiesToVisit[i]][citiesToVisit[j]];

    int startIndex = 0;
    for (int i = 0; i < k; ++i)
        if (citiesToVisit[i] == startCity) startIndex = i;

    vector<vector<int>> dp(1 << k, vector<int>(k, -1));
    vector<vector<int>> parent(1 << k, vector<int>(k, -1));

    int result = tsp(1 << startIndex, startIndex, reduced, dp, parent, startIndex, k);

    cout << "\nMinimum travel cost: " << result << endl;
    printPath(1 << startIndex, startIndex, parent, citiesToVisit, startIndex);
}

// Main menu display function
void showMainMenu( User &user ,unordered_map<int,City> cities, vector<vector<pair<int, int>>> graph)
{
    int choice;
    do
    {
        printMenu();
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
           case 1:
                user.displayProfile();
                break;

           case 2:
               disAndPath(cities,graph);
               break;

          case 3:
               customized_TSP(cities,graph);
               break;

          case 4:

               printCities(cities);
               break;

          case 5:
               cityInformation(cities);
               break;

          case 6:
               allCityDistance(cities,graph);
               break;

          case 7:
               budgetManagement(cities);
               break;

          case 8:
               splitExpenses();
               break;

          case 9:
               cout << "\nExiting TravelMate. Have a great journey!\n";
               break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }



    }while(choice!=8);
}

int main(){
    loadUsers();
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
        bool verfied=false;
        string email="";
        switch (choice)
        {
        case 1:
            verfied=signup(email);
            break;

        case 2:
            verfied = login(email);
            break;

        case 3:
            cout << "Thank You for using TravelMate" << endl;
            break;

        default:
            cout << endl
                 << "Invalid choice. Try again.\n";
        }

        if(verfied==true){
            currentUser=users[email];
            unordered_map<int, City >cities = createCitiesData();
                        cout<<"verified";

            vector<vector<pair<int, int>>> graph = createCityGraph();
            showMainMenu(currentUser, cities, graph);
        }

    } while (choice != 3);

    return 0;
}
