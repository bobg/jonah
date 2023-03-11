#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include "treemm.h"
#include <string>
#include <vector>

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
      bool m_loaded;
      TreeMultimap<std::string, Movie*> m_moviesID;
      TreeMultimap<std::string, Movie*> m_moviesDirector;
      TreeMultimap<std::string, Movie*> m_moviesActor;
      TreeMultimap<std::string, Movie*> m_moviesGenre;
      vector<Movie*> m_death;
};

#endif // MOVIEDATABASE_INCLUDED
