#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const int CITY_COUNT = 16;
const int INF = 1000000000;

class User {
public:
    string name;
    string email;
    string password;

    User() = default;
    User(const string& name, const string& email, const string& password);

    void displayProfile() const;
};

class Destination {
public:
    string name;
    int cost;
    int enjoyment;
    string description;
    int duration;

    Destination() = default;
    Destination(const string& name, int cost, int enjoyment,
                const string& description, int duration);
};

class City {
public:
    string name;
    int id;
    string weather;
    vector<Destination> destinations;

    City() = default;
    City(const string& name, int id, const string& weather,
         const vector<Destination>& destinations);
};

extern const vector<string> cityNames;

bool isValidCityId(int cityId);
unordered_map<int, City> createCitiesData();
