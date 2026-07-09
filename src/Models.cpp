#include "Models.h"

#include <iostream>

using namespace std;

const vector<string> cityNames = {
    "Delhi", "Mumbai", "Jaipur", "Agra", "Kolkata", "Bengaluru", "Hyderabad",
    "Udaipur", "Varanasi", "Amritsar", "Chennai", "Mysuru", "Pune", "Goa",
    "Rishikesh", "Darjeeling"
};

User::User(const string& name, const string& email, const string& password)
    : name(name), email(email), password(password) {}

void User::displayProfile() const {
    cout << "\n----------------------------\n"
         << "      User Profile\n"
         << "----------------------------\n"
         << "   Name  : " << name << '\n'
         << "   Email : " << email << '\n'
         << "----------------------------\n\n";
}

Destination::Destination(const string& name, int cost, int enjoyment,
                         const string& description, int duration)
    : name(name), cost(cost), enjoyment(enjoyment),
      description(description), duration(duration) {}

City::City(const string& name, int id, const string& weather,
           const vector<Destination>& destinations)
    : name(name), id(id), weather(weather), destinations(destinations) {}

bool isValidCityId(int cityId) {
    return cityId >= 0 && cityId < CITY_COUNT;
}

unordered_map<int, City> createCitiesData() {
    unordered_map<int, City> cities;

    cities[0] = {"Delhi", 0, "Hot in summer, cold in winter", {
        {"Red Fort", 500, 8, "Historic fort and UNESCO site.", 2},
        {"India Gate", 0, 7, "War memorial and picnic spot.", 1},
        {"Qutub Minar", 300, 8, "UNESCO world heritage site.", 2},
        {"Lotus Temple", 0, 7, "Baha'i House of Worship with unique architecture.", 1},
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
        {"Ramoji Film City", 1150, 9, "World's largest film studio complex.", 4},
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
        {"St. Philomena's Church", 0, 7, "Neo-Gothic church.", 1},
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
