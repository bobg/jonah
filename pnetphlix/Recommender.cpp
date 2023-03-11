#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void isCompatible(vector<MovieAndRank>& mandr, string mID, int points) {
    //cout << "in is compatible" << endl;
    for (int i = 0; i < mandr.size(); i++) {
        if (mandr[i].movie_id == mID) {
            mandr[i].compatibility_score += points;
            return;
        }
    }
    mandr.push_back(MovieAndRank(mID, points));
    return;
}

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database) : m_ud(user_database), m_md(movie_database)
{
    // Replace this line with correct code.
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    cout << "in recommend_movies function" << endl;
    vector<MovieAndRank> mandr;

    if (movie_count <= 0) {
        cout << "movie count less than or equal to 0" << endl;
        return mandr;
    }

    User* user = m_ud.get_user_from_email(user_email);
    if (user == nullptr) {
        cout << "invalid user" << endl;
        return mandr;
    }
    vector<string> watchHistory = user->get_watch_history();
    for (int i = 0; i < watchHistory.size(); i++) {
        cout << "new i loop iteration at i = " << i << endl;
        Movie* movie = m_md.get_movie_from_id(watchHistory[i]);
        vector<string> directors = movie->get_directors();
        for (int j = 0; j < directors.size(); j++) {
            vector<Movie*> movie_from_director = m_md.get_movies_with_director(directors[j]);
            for (int k = 0; k < movie_from_director.size(); k++) {
                isCompatible(mandr, movie_from_director[k]->get_id(), 20);
            }
        }
        vector<string> actors = movie->get_actors();
        for (int j = 0; j < actors.size(); j++) {
            vector<Movie*> movie_from_actor = m_md.get_movies_with_actor(actors[j]);
            for (int k = 0; k < movie_from_actor.size(); k++) {
                isCompatible(mandr, movie_from_actor[k]->get_id(), 30);
            }
        }
        vector<string> genres = movie->get_genres();
        for (int j = 0; j < genres.size(); j++) {
            vector<Movie*> movie_from_genre = m_md.get_movies_with_genre(genres[j]);
            for (int k = 0; k < movie_from_genre.size(); k++) {
                isCompatible(mandr, movie_from_genre[k]->get_id(), 1);
            }
        }
    }

    for (vector<MovieAndRank>::iterator i = mandr.begin(); i != mandr.end();/*no increment*/) {
        bool erased = false;
        MovieAndRank a = *i;
        for (int j = 0; j < watchHistory.size(); j++) {
            if (watchHistory[j] == a.movie_id) {
                i = mandr.erase(i);
                erased = true;
                cout << "removing duplicate" << endl;
                break;
            }
        }
        if (erased == false) {
            i++;
        }
    }

    sort(mandr.begin(), mandr.end(), Comparer(m_md));

    if (mandr.size() > movie_count) {
        mandr.erase(mandr.begin() + movie_count, mandr.end());
    }

    cout << "end of function" << endl;
    return mandr;  // Replace this line with correct code.
}

//===================================================================================

bool Recommender::Comparer::operator()(const MovieAndRank& i, const MovieAndRank& j) const {
    if (i.compatibility_score > j.compatibility_score) {
        return true;
    }
    else if (i.compatibility_score == j.compatibility_score) {
        string i_id = i.movie_id;
        string j_id = j.movie_id;
        Movie* movie_i = m_md.get_movie_from_id(i_id);
        Movie* movie_j = m_md.get_movie_from_id(j_id);
        if (movie_i->get_rating() > movie_j->get_rating()) {
            return true;
        }
        else if (movie_i->get_rating() == movie_j->get_rating()) {
            if (movie_i->get_title() < movie_j->get_title()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}