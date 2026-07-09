#include "UserManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

unordered_map<string, User> users;

const string USER_FILE_PATH = "data/Users.txt";

bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    if (atPos == string::npos || email.find('@', atPos + 1) != string::npos) {
        return false;
    }

    size_t dotPos = email.find('.', atPos + 1);
    return dotPos != string::npos && dotPos > atPos + 1 && dotPos + 1 < email.size();
}

bool isValidPassword(const string& password) {
    return password.length() >= 6;
}

vector<string> splitUserRecord(const string& line) {
    vector<string> parts;
    string part;
    stringstream ss(line);

    while (getline(ss, part, '|')) {
        parts.push_back(part);
    }

    return parts;
}

void loadUsers() {
    ifstream file(USER_FILE_PATH);

    if (!file.is_open()) {
        cout << "Note: data/Users.txt file not found. Starting with empty user database.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        vector<string> parts = splitUserRecord(line);
        if (parts.size() != 3) {
            continue;
        }

        users[parts[1]] = User(parts[0], parts[1], parts[2]);
    }
}

void saveUser(const User& user) {
    ofstream file(USER_FILE_PATH, ios::app);

    if (!file.is_open()) {
        cout << "Error opening data/Users.txt file for writing.\n";
        return;
    }

    file << user.name << '|' << user.email << '|' << user.password << '\n';
}

bool signup(string& mail) {
    string name;
    string email;
    string password;

    cout << "\n=== Sign Up ===\n";
    cout << "Enter your name: ";
    getline(cin >> ws, name);

    cout << "Enter your email: ";
    cin >> email;

    if (!isValidEmail(email)) {
        cout << "Invalid email format. Email must contain one '@' and a '.' after '@'.\n";
        return false;
    }

    if (users.find(email) != users.end()) {
        cout << "Account already exists. Try logging in.\n";
        return false;
    }

    cout << "Create a password: ";
    cin >> password;

    if (!isValidPassword(password)) {
        cout << "Password must be at least 6 characters long.\n";
        return false;
    }

    // For a production application, passwords should be salted and hashed instead of stored in plain text.
    User user(name, email, password);
    users[email] = user;
    saveUser(user);
    mail = email;

    cout << "\nSign up successful. Logging you in now...\n";
    return true;
}

bool login(string& mail) {
    string email;
    string password;

    cout << "\n=== Login ===\n";
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> password;

    auto userIt = users.find(email);
    if (userIt != users.end() && userIt->second.password == password) {
        cout << "\nLogin successful. Welcome, " << userIt->second.name << "!\n";
        mail = email;
        return true;
    }

    cout << "\nInvalid email or password.\n";
    return false;
}
