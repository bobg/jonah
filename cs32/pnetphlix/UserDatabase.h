#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
      bool m_loaded;
      TreeMultimap<std::string, User*> m_users;
      vector<User*> m_death;
};

#endif // USERDATABASE_INCLUDED
