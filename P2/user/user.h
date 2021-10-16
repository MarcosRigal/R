#ifndef USER_H
#define USER_H

#include <string.h>

using namespace std;

class User
{
private:
    char name_[250];
    char password_[250];
    bool isWaiting_;

public:
    User() { isWaiting_ = true; }

    inline char *getUserName() { return name_; }
    inline char *getUserPassword() { return password_; }
    inline bool getUserStatus() { return isWaiting_; }

    inline void setUserName(char *name) { strncpy(name_, name, 250); }
    inline void setUserName(const char *name) { strncpy(name_, name, 250); }

    inline void setUserPassword(char *password) { strncpy(password_, password, 250); }
    inline void setUserPassword(const char *password) { strncpy(password_, password, 250); }

    inline void setUserStatus(bool isWaiting) { isWaiting_ = isWaiting; }
};

#endif