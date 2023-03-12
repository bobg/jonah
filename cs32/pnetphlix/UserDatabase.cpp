#include "UserDatabase.h"
#include "User.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
    m_loaded = false;
    // Replace this line with correct code.
}

UserDatabase::~UserDatabase()
{
    for (vector<User*>::iterator it = m_death.begin(); it != m_death.end(); it++) {
        delete* it;
    }
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);

    if (m_loaded == true) {
        return false;
    }

    while (true) {
        if (infile.eof()) { 
            break; 
        }
        string name;
        if (!getline(infile, name)) {
            break;
        }
        string email;
        getline(infile, email);
        string movie_count_string;
        getline(infile, movie_count_string);
        int movie_count_int = stoi(movie_count_string);
        vector<string> watchHistory;
        for (int i = 0; i < movie_count_int; i++) {
            string watchHistory_string;
            getline(infile, watchHistory_string);
            watchHistory.push_back(watchHistory_string);
        }

        User* user = new User(name, email, watchHistory);

        m_users.insert(email, user);
        m_death.push_back(user);

        string blank;
        if (!getline(infile, blank)) {
            break;
        }

    }

    m_loaded = true;
    return m_loaded;  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator it = m_users.find(email);
    if (it.is_valid()) {
        User* user = it.get_value();
        return user;
    }
    else {
        return nullptr;  // Replace this line with correct code.
    }
}
