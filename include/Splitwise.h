#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Splitwise {
public:
    string name;
    vector<string> members;
    unordered_map<string, unordered_map<string, double>> balance;

    bool addMember(const string& memberName);
    bool hasMember(const string& memberName) const;
    bool addExpense(const string& paidBy, double amount, const vector<string>& splitBetween);
    void showBalances() const;

private:
    unordered_set<string> memberSet;
};

void manageGroupExpenses();
