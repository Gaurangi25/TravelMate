void loadUsers(){
    fstream file;
    file.open("Users.txt", ios::in | ios::out);
    string name, email, password;
    if (!file.is_open())
    {
        cout << "Note: Users.txt file not found. Starting with empty user database.\n";
        return;
    }

    while (file >> name >> email >> password)
    {
        users[email] = User(name, email, password);
    }
    file.close();
}

void saveUser(User &user){
    fstream file;
    file.open("Users.txt", ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening Users.txt file!" << endl;
        return;
    }
    file << user.name << " " << user.email << " " << user.password << endl;
    file.close();
    cout << "User appended to file successfully." << endl;
}
