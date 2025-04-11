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

void findShortestRoute()
{
    cout << "\nFinding the shortest route using Dijkstra...\n";
    // Your Dijkstra logic goes here
}

void planTrip()
{
    cout << "\nPlanning your multi-city trip...\n";
    // Your TSP or Floyd-Warshall logic goes here
}

// file handling
void loadUsers()
{
    ifstream file("Users.txt");
    string name, email, password;

    while (file >> name >> email >> password)
    {
        users[email] = User(name, email, password);
    }

    file.close();
}

// display information of saved user
void saveUser(User &user)
{
    ofstream file("Users.txt", ios::app);
    file << user.name << " " << user.email << " " << user.password << endl;
    file.close();
}

// display main menu of TravelMate
void showMainMenu(User &user)
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
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            user.displayProfile();
            break;
        case 2:
            findShortestRoute(); // for Dijkstra
            break;
        case 3:
            planTrip(); // for multi-city trip planning
            break;
        case 4:
            cout << "\nExiting TravelMate. Have a great journey!\n";
            break;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// signup function
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
        cout << "Account already exists ! Try logging in.\n";
        return false;
    }

    cout << "Create a password: ";
    cin >> password;

    User user(name, email, password);
    users[email] = user;
    saveUser(user);

    cout << "\nSign Up successful!! Logging you in now...\n";

    showMainMenu(user);
    return true;
}

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
        cout << "\nLogin suucessful! Welcome, " << users[email].name << "!" << endl;
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
                showMainMenu(currentUser);
            break;

        case 3:
            cout << "Thank You for using TravelMate" << endl;
            break;

        default:
            cout << endl
                 << "Invalide choice. Try again<<endl";
        }
    } while (choice != 3);

    return 0;
}
