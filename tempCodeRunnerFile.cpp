void showMainMenu(User &user, vector<City> &cities, vector<vector<pair<int, int>>> &graph)
{
    int choice;
    do
    {
        cout << "=========================================================\n";
        cout << "TravelMate - Main Menu\n";
        cout << "=========================================================\n";
        cout << "1. View My Profile\n";
        cout << "2. Find Shortest Route Between Cities\n";
        cout << "3. Plan My Trip\n";
        cout << "4. View All Cities\n";
        cout << "5. View City Information\n";
        cout << "6. Group Expense Split (Splitwise)\n";
        cout << "7. Travel Budget Management\n";
        cout << "8. Update Profile\n";
        cout << "9. Logout\n";
        cout << "10. Delete My Account\n";
        cout << "11. Exit\n";

        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            user.displayProfile();
            break;

        case 2:
        {
            int src, dest;
            cout << "\nAvailable cities:\n";
            for (int i = 0; i < cities.size(); i++)
            {
                cout << i << " - " << cities[i].name << endl;
            }

            cout << "\nEnter source city index (0-" << cities.size() - 1 << "): ";
            cin >> src;
            cout << "Enter destination city index (0-" << cities.size() - 1 << "): ";
            cin >> dest;
            if (src >= 0 && src < cities.size() && dest >= 0 && dest < cities.size())
            {
                findShortestRoute(src, dest, graph, cities);
            }
            else
            {
                cout << "Invalid city index. Please try again.\n";
            }
        }
        break;

        case 3:
            planTrip(cities, graph);
            break;

        case 4:
        {
            cout << "\nList of available cities:\n";
            for (int i = 0; i < cities.size(); i++)
            {
                cout << i << " - City " << cities[i].name << "\n";
                cout << "   Destinations in this city:\n";
                for (auto &dest : cities[i].destinations)
                {
                    cout << "   - " << dest.name << " (Cost: " << dest.cost
                         << ", Enjoyment: " << dest.enjoyment << ")\n";
                }
                cout << endl;
            }
        }
        break;

        case 5:
        {
            int cityIndex;
            cout << "\nEnter the city index (0-" << cities.size() - 1 << ") to view information: ";
            cin >> cityIndex;
            cout << "\n-------------------------------------------------------------------\n";
            if (cityIndex >= 0 && cityIndex < cities.size())
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
        break;

        case 6:
        {
            TripGroup group;
            int numMembers;
            cout << "\nEnter number of travelers in the group: ";
            cin >> numMembers;

            cin.ignore(); // Clear newline buffer
            for (int i = 0; i < numMembers; ++i)
            {
                string name;
                cout << "Enter name of traveler " << (i + 1) << ": ";
                getline(cin, name);
                group.addMember(name);
            }

            int addMore;
            do
            {
                string expenseName;
                int amount, payerIndex;

                cout << "\nEnter expense name: ";
                getline(cin, expenseName);
                cout << "Enter amount: ";
                cin >> amount;

                cout << "Who paid for this? Select index:\n";
                for (int i = 0; i < group.members.size(); ++i)
                    cout << i << " - " << group.members[i] << endl;
                cout << "Enter payer index: ";
                cin >> payerIndex;
                cin.ignore();

                group.addExpense(expenseName, amount, payerIndex);

                cout << "Do you want to add another expense? (1 = Yes, 0 = No): ";
                cin >> addMore;
                cin.ignore();
            } while (addMore == 1);

            group.calculateShares();
        }
        break;

        case 7:
        {
            // double budget;
            // cout << "\nEnter your travel budget: ";
            // cin >> budget;

            // // Instead of just printing a suggestion, use the Knapsack algorithm
            // optimalTravelItinerary(cities, (int)budget);

            manageBudget();
            break;
        }

        case 8:
        {
            string newName, newEmail, newPassword;
            cout << "\nEnter new name (or press enter to skip): ";
            getline(cin >> ws, newName);
            cout << "Enter new email (or press enter to skip): ";
            getline(cin >> ws, newEmail);
            cout << "Enter new password (or press enter to skip): ";
            getline(cin >> ws, newPassword);

            // Update profile if new details are provided
            if (!newName.empty())
                user.name = newName;
            if (!newEmail.empty())
            {
                // If email is changing, update the users map
                if (newEmail != user.email)
                {
                    users.erase(user.email);
                    user.email = newEmail;
                    users[newEmail] = user;
                }
                else
                {
                    user.email = newEmail;
                }
            }
            if (!newPassword.empty())
                user.password = newPassword;

            users[user.email] = user; // Update the user in the users map
            saveUser(user);           // Save updated profile to file
            cout << "\nProfile updated successfully!\n";
        }
        break;

        case 9:
            cout << "\nLogging out...\n";
            return; // Return to the login menu

        case 10:
        {
            char confirm;
            cout << "\nAre you sure you want to delete your account? (Y/N): ";
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                users.erase(user.email); // Remove user from the system
                // Delete from file as well
                saveUser(user);
                cout << "\nAccount deleted successfully.\n";
                return; // Return to the login menu
            }
            else
            {
                cout << "\nAccount deletion canceled.\n";
            }
        }
        break;

        case 11:
            cout << "\nExiting TravelMate. Have a great journey!\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 11);
}
