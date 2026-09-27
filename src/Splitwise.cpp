#include "Splitwise.h"

#include "InputUtils.h"

#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

bool Splitwise::addMember(const string& memberName) {
    if (memberName.empty() || memberSet.count(memberName)) {
        return false;
    }
    members.push_back(memberName);
    memberSet.insert(memberName);
    return true;
}

bool Splitwise::hasMember(const string& memberName) const {
    return memberSet.count(memberName) > 0;
}

bool Splitwise::addExpense(const string& paidBy, double amount, const vector<string>& splitBetween) {
    if (!hasMember(paidBy) || amount <= 0.0 || splitBetween.empty()) {
        return false;
    }

    unordered_set<string> seen;
    for (const string& person : splitBetween) {
        if (!hasMember(person) || seen.count(person)) {
            return false;
        }
        seen.insert(person);
    }

    double splitAmount = amount / static_cast<double>(splitBetween.size());
    for (const string& person : splitBetween) {
        if (person == paidBy) {
            continue;
        }
        balance[person][paidBy] += splitAmount;
        balance[paidBy][person] -= splitAmount;
    }

    return true;
}

void Splitwise::showBalances() const {
    const double EPSILON = 0.01;
    bool hasBalance = false;

    cout << fixed << setprecision(2);
    cout << "\nFinal Balances:\n";

    for (const string& a : members) {
        auto outer = balance.find(a);
        if (outer == balance.end()) {
            continue;
        }
        for (const string& b : members) {
            auto inner = outer->second.find(b);
            if (inner != outer->second.end() && inner->second > EPSILON) {
                cout << a << " owes " << b << " Rs. " << inner->second << '\n';
                hasBalance = true;
            }
        }
    }

    if (!hasBalance) {
        cout << "No outstanding direct balances.\n";
    }
}

void manageGroupExpenses() {
    Splitwise splitwise;
    int memberCount;
    int expenseCount;

    cout << "\nEnter group name: ";
    if (!(cin >> ws) || !getline(cin, splitwise.name)) {
        return;
    }

    if (!readInt("Enter number of members: ", memberCount)) {
        return;
    }

    if (memberCount <= 0) {
        cout << "Number of members must be positive.\n";
        return;
    }

    for (int i = 1; i <= memberCount; ++i) {
        string member;
        cout << "Enter member name " << i << ": ";
        cin >> member;

        if (!splitwise.addMember(member)) {
            cout << "Invalid or duplicate member name. Please restart group expense entry.\n";
            return;
        }
    }

    if (!readInt("\nEnter number of expenses: ", expenseCount)) {
        return;
    }

    if (expenseCount < 0) {
        cout << "Number of expenses cannot be negative.\n";
        return;
    }

    for (int i = 1; i <= expenseCount; ++i) {
        string paidBy;
        double amount;
        int splitCount;

        cout << "\nExpense " << i << ":\n";
        cout << "Paid by: ";
        cin >> paidBy;
        if (!readDouble("Amount: ", amount) ||
            !readInt("Number of people involved in this expense: ", splitCount)) {
            return;
        }

        if (amount <= 0.0) {
            cout << "Invalid expense skipped: amount must be positive.\n";
            continue;
        }

        if (splitCount <= 0) {
            cout << "Invalid expense skipped: split group cannot be empty.\n";
            continue;
        }

        vector<string> splitBetween;
        cout << "Enter names of people to split between:\n";
        for (int j = 1; j <= splitCount; ++j) {
            string name;
            cin >> name;
            splitBetween.push_back(name);
        }

        if (!splitwise.addExpense(paidBy, amount, splitBetween)) {
            cout << "Invalid expense skipped. Check payer, split members, and duplicate names.\n";
        }
    }

    splitwise.showBalances();
}
