# TravelMate - Algorithmic Travel Planning System

TravelMate is a C++ console-based travel planning system that applies graph algorithms and dynamic programming to solve route optimization, multi-city trip planning, and budget-constrained destination selection problems.

## 1. Project Overview

TravelMate is designed as a DSA and OOP-focused academic project. It keeps travel data predefined and demonstrates how classic algorithms can be mapped to practical planning features such as finding shortest routes, planning a round trip, choosing destinations under a budget, and tracking direct group expenses.

## 2. Key Features

- User signup and login using local file handling
- User profile display
- Predefined Indian city and destination dataset
- Shortest path between two cities
- Shortest distances from one city to all cities
- Optimal round trip planning across selected cities
- Destination budget optimizer
- Group expense split using direct balances
- City information with weather, destination cost, enjoyment, and duration

## 3. Algorithms Used

**Dijkstra's Algorithm**  
Used to find the shortest route and distance between two cities.

**Floyd-Warshall Algorithm**  
Used to compute all-pairs shortest distances and preprocess distances for selected cities before TSP optimization.

**Travelling Salesman Problem with Bitmask DP**  
Used to calculate the minimum-distance round trip across user-selected cities.

**0/1 Knapsack Dynamic Programming**  
Used to maximize total destination enjoyment within a fixed travel budget.

**Hash Maps**  
Used for user lookup and direct group expense balance tracking.

## 4. Algorithm-to-Feature Mapping

| Feature | Algorithm / Data Structure |
| --- | --- |
| Find shortest path between two cities | Dijkstra's Algorithm |
| View shortest distances from one city | Floyd-Warshall Algorithm |
| Plan optimal round trip | Floyd-Warshall + TSP Bitmask DP |
| Destination budget optimizer | 0/1 Knapsack DP |
| Login and member lookup | Hash Maps |
| Group expense balance tracking | Nested Hash Maps |

## 5. Project Architecture

The project is split into small modules so each responsibility is easy to explain:

- `Models` stores the core classes and predefined city data.
- `GraphAlgorithms` stores graph creation, Dijkstra, and Floyd-Warshall logic.
- `TripPlanner` stores user-facing travel planning features, Knapsack DP, and TSP DP.
- `Splitwise` stores group member and direct expense balance logic.
- `UserManager` stores signup, login, validation, and file handling.
- `main.cpp` contains menus and high-level navigation.

## 6. Project Structure

```text
TravelMate/
|-- include/
|   |-- Models.h
|   |-- GraphAlgorithms.h
|   |-- InputUtils.h
|   |-- TripPlanner.h
|   |-- Splitwise.h
|   |-- UserManager.h
|-- src/
|   |-- Models.cpp
|   |-- GraphAlgorithms.cpp
|   |-- InputUtils.cpp
|   |-- TripPlanner.cpp
|   |-- Splitwise.cpp
|   |-- UserManager.cpp
|   |-- main.cpp
|-- data/
|   |-- Users.example.txt
|-- README.md
|-- .gitignore
```

`data/Users.txt` is created/used locally for signup and login data and is ignored by Git because it stores plain-text educational credentials.

## 7. How It Works

1. The user signs up or logs in.
2. The application loads predefined cities and an undirected weighted graph of distances.
3. The user selects a travel feature from the main menu.
4. The selected feature calls the relevant algorithm and prints a console-friendly result.

## 8. Time and Space Complexities

| Algorithm | Time Complexity | Space Complexity |
| --- | --- | --- |
| Dijkstra's Algorithm | O((V + E) log V) | O(V) |
| Floyd-Warshall Algorithm | O(V^3) | O(V^2) |
| TSP with Bitmask DP | O(2^K * K^2) | O(2^K * K) |
| 0/1 Knapsack DP | O(N * Budget) | O(N * Budget) |

`V` is the number of cities, `E` is the number of graph edges, `K` is the number of selected cities for TSP, and `N` is the number of destinations in a city.

## 9. How to Compile and Run

Compile with any C++17 compiler.

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o TravelMate
./TravelMate
```

On Windows PowerShell with MinGW:

```powershell
g++ -std=c++17 -Iinclude src/*.cpp -o TravelMate.exe
.\TravelMate.exe
```

## 10. Sample Workflow

Shortest path example:

```text
=== Login ===
Email: gaurangi@example.com
Password: password123

Login successful. Welcome, Gaurangi Agarwal!

Choose an option: 2
Enter current city ID (0-15): 0
Enter destination city ID (0-15): 7

Shortest distance from Delhi to Udaipur: 670 km
Path: Delhi -> Jaipur -> Udaipur
```

Destination Budget Optimizer example:

```text
Choose an option: 7
Enter the city ID you want to visit: 2
Enter your destination budget: 550

Destination Budget Optimizer for Jaipur
Maximum Enjoyment: 30

Recommended Destinations:
1. Hawa Mahal - Rs. 100
2. City Palace - Rs. 200
3. Jantar Mantar - Rs. 50
4. Nahargarh Fort - Rs. 100

Total Cost: Rs. 450
Remaining Budget: Rs. 100
```

Optimal Round Trip with Itinerary Breakdown example:

```text
Choose an option: 3
Enter number of cities to visit (1-16): 3
Enter city IDs to visit:
City 1: 0
City 2: 2
City 3: 3
Enter starting city ID: 0

Minimum Travel Distance: 750 km

Optimal Round Trip Route:
Delhi -> Jaipur -> Agra -> Delhi

View destination enjoyment, price, and duration breakdown for this route? (1 = Yes, 0 = No): 1

=========================================================================================
                     Optimal Trip Itinerary Breakdown (Cost & Enjoyment)
=========================================================================================

Stop 1: Delhi [Weather: Hot in summer, cold in winter]
-----------------------------------------------------------------------------------------
Tourist Destination                   Cost (Rs.)    Enjoyment     Duration
-----------------------------------------------------------------------------------------
Red Fort                              Rs. 500       8/10          2 hours
India Gate                            Rs. 0         7/10          1 hour
Qutub Minar                           Rs. 300       8/10          2 hours
Lotus Temple                          Rs. 0         7/10          1 hour
Humayun's Tomb                        Rs. 250       8/10          2 hours
-----------------------------------------------------------------------------------------
City Subtotal -> Cost: Rs. 1050 | Enjoyment: 38 pts | Sightseeing Time: 8 hrs

Stop 2: Jaipur [Weather: Hot and dry]
-----------------------------------------------------------------------------------------
...
=========================================================================================
                               Overall Itinerary Summary
=========================================================================================
Total Travel Distance     : 750 km
Total Destination Cost    : Rs. 2075
Total Potential Enjoyment : 117 points
Total Sightseeing Duration: 29 hours
=========================================================================================
```

## 11. Limitations

- City and destination data is predefined.
- Distances are static and do not use live maps or traffic data.
- Authentication uses local file storage.
- Password storage is simplified for educational purposes.
- Expense splitting tracks direct balances and does not perform debt simplification.
- TSP Bitmask DP is suitable only for a limited number of selected cities due to exponential state growth.

## 12. Future Improvements

- Live map and distance API integration
- Database-backed user management
- Secure password hashing
- Dynamic city and destination data
- Time-constrained itinerary planning using destination duration
- Minimum cash flow debt simplification
- Unit tests

## 13. Author

Gaurangi Agarwal
