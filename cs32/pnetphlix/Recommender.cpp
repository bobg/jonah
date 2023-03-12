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

void addPoints(vector<MovieAndRank>& mandr, string mID, int points) {
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
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<MovieAndRank> mandr;

    if (movie_count <= 0) {
        return mandr;
    }

    User* user = m_ud.get_user_from_email(user_email);
    if (user == nullptr) {
        return mandr;
    }
    vector<string> watchHistory = user->get_watch_history();
    for (int i = 0; i < watchHistory.size(); i++) {
        const string& movie_id = watchHistory[i];

        cout << "new i loop iteration at i = " << i << endl;
        Movie* movie = m_md.get_movie_from_id(movie_id);

        vector<string> directors = movie->get_directors();
        for (int j = 0; j < directors.size(); j++) {
            const string& director = directors[j];

            bool seen = false;
            for (int jj = 0; jj < j; jj++) {
              if (director == directors[jj]) {
                seen = true;
                break;
              }
            }
            if (seen) {
              continue;
            }

            vector<Movie*> movies_from_director = m_md.get_movies_with_director(director);
            for (int k = 0; k < movies_from_director.size(); k++) {
                addPoints(mandr, movies_from_director[k]->get_id(), 20);
            }
        }

        vector<string> actors = movie->get_actors();
        for (int j = 0; j < actors.size(); j++) {
            const string& actor = actors[j];

            bool seen = false;
            for (int jj = 0; jj < j; jj++) {
              if (actor == actors[jj]) {
                seen = true;
                break;
              }
            }
            if (seen) {
              continue;
            }

            vector<Movie*> movies_from_actor = m_md.get_movies_with_actor(actor);
            for (int k = 0; k < movies_from_actor.size(); k++) {
                addPoints(mandr, movies_from_actor[k]->get_id(), 30);
            }
        }

        vector<string> genres = movie->get_genres();
        for (int j = 0; j < genres.size(); j++) {
            const string& genre = genres[j];

            bool seen = false;
            for (int jj = 0; jj < j; jj++) {
              if (genre == genres[jj]) {
                seen = true;
                break;
              }
            }
            if (seen) {
              continue;
            }

            vector<Movie*> movies_from_genre = m_md.get_movies_with_genre(genre);
            for (int k = 0; k < movies_from_genre.size(); k++) {
                addPoints(mandr, movies_from_genre[k]->get_id(), 1);
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

    return mandr;
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