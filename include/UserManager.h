#pragma once

#include "Models.h"

#include <string>
#include <unordered_map>

using namespace std;

extern unordered_map<string, User> users;

bool isValidEmail(const string& email);
bool isValidPassword(const string& password);
void loadUsers();
void saveUser(const User& user);
bool signup(string& mail);
bool login(string& mail);
