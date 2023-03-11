#include "MovieDatabase.h"
#include "UserDatabase.h"
#include "Movie.h"
#include "User.h"
#include "Recommender.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

int main()
{
	UserDatabase udb;
	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
	MovieDatabase mdb;
	if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
		return 1;
	}
	Recommender r(udb, mdb);
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
			cout << "Found " << u->get_full_name() << endl;

		vector<MovieAndRank> mandr = r.recommend_movies(email, 5);
		for (int i = 0; i < mandr.size(); i++) {
			cout << mandr[i].movie_id << endl;
			cout << mandr[i].compatibility_score << endl;
		}
	}
}
