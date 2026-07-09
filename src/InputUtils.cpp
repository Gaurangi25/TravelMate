#include "InputUtils.h"

#include <iostream>
#include <limits>

using namespace std;

bool readInt(const string& prompt, int& value) {
    cout << prompt;
    if (cin >> value) {
        return true;
    }

    cout << "Invalid input. Please enter a valid number.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

bool readDouble(const string& prompt, double& value) {
    cout << prompt;
    if (cin >> value) {
        return true;
    }

    cout << "Invalid input. Please enter a valid number.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}
