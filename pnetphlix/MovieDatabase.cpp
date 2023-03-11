#include "MovieDatabase.h"
#include "Movie.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string s) {
    string delimiter = ",";
    int pos = 0;
    std::string token;
    vector<string> result;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);
    return result;
}

MovieDatabase::MovieDatabase()
{
    m_loaded = false;
    // Replace this line with correct code.
}

MovieDatabase::~MovieDatabase()
{
    for (vector<Movie*>::iterator it = m_death.begin(); it != m_death.end(); it++) {
        delete* it;
    }
}

bool MovieDatabase::load(const string& filename)
{
    //cout << "begin movie load" << endl;
    ifstream infile(filename);

    if (m_loaded == true) {
        return false;
    }

    while (true) {
        string id;
        if (!getline(infile, id)) {
            break;
        }
        string title;
        getline(infile, title);

        string release_year;
        getline(infile, release_year);

        string directors_string;
        getline(infile, directors_string);
        vector<string> directors = split(directors_string);

        string actors_string;
        getline(infile, actors_string);
        vector<string> actors = split(actors_string);

        string genres_string;
        getline(infile, genres_string);
        vector<string> genres = split(genres_string);

        string rating_string;
        getline(infile, rating_string);
        float rating = stof(rating_string);

        Movie* movie = new Movie(id, title, release_year, directors, actors, genres, rating);

        m_moviesID.insert(id, movie);

        for (vector<string>::iterator it = directors.begin(); it != directors.end(); it++) {
            m_moviesDirector.insert(*it, movie);
        }
        for (vector<string>::iterator it = actors.begin(); it != actors.end(); it++) {
            m_moviesActor.insert(*it, movie);
        }
        for (vector<string>::iterator it = genres.begin(); it != genres.end(); it++) {
            m_moviesGenre.insert(*it, movie);
        }

        m_death.push_back(movie);

        string blank;
        if (!getline(infile, blank)) {
            break;
        }
    }
    m_loaded = true;
    //cout << "end movie load" << endl;
    return m_loaded;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<string, Movie*>::Iterator it = m_moviesID.find(id);
    if (it.is_valid()) {
        Movie* movie = it.get_value();
        return movie;
    }
    else {
        return nullptr;  // Replace this line with correct code.
    }
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> result;
    TreeMultimap<string, Movie*>::Iterator it = m_moviesDirector.find(director);
    while (it.is_valid()) {
        Movie* movie = it.get_value();
        result.push_back(movie);
        it.advance();
    }
    return result;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> result;
    TreeMultimap<string, Movie*>::Iterator it = m_moviesActor.find(actor);
    while (it.is_valid()) {
        Movie* movie = it.get_value();
        result.push_back(movie);
        it.advance();
    }
    return result;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> result;
    TreeMultimap<string, Movie*>::Iterator it = m_moviesGenre.find(genre);
    while (it.is_valid()) {
        Movie* movie = it.get_value();
        result.push_back(movie);
        it.advance();
    }
    return result;  // Replace this line with correct code.
}