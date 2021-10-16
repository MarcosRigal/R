#ifndef USER_H
#define USER_H

#include <string.h>

using namespace std;

class User
{
private:
    int userSocket_;
    char name_[250];
    char password_[250];
    bool isWaiting_;

public:
    User() { isWaiting_ = true; }

    inline int getUserSocket() { return userSocket_; }

    inline char *getUserName() { return name_; }

    inline char *getUserPassword() { return password_; }

    inline bool getUserStatus() { return isWaiting_; }

    inline void setUserSocket(int userSocket) { userSocket_ = userSocket; }

    inline void setUserName(char *name) { strncpy(name_, name, 250); }
    inline void setUserName(const char *name) { strncpy(name_, name, 250); }

    inline void setUserPassword(char *password) { strncpy(password_, password, 250); }
    inline void setUserPassword(const char *password) { strncpy(password_, password, 250); }

    inline void setUserStatus(bool isWaiting) { isWaiting_ = isWaiting; }
};

#endif