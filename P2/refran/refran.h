#ifndef REFRAN_H
#define REFRAN_H

using namespace std;

class Refran
{
private:
    int userSocket_;
    char refran_[250];
    char refranOculto_[250];

public:
    Refran(int userSocket);

    inline int getUserSocket() { return userSocket_; }
    inline char *getRefran() { return refran_; }
    inline char *getRefranOculto() { return refranOculto_; }

    inline void setUserSocket(int userSocket) { userSocket_ = userSocket; }
    inline void setRefran(char *refran) { strncpy(refran_, refran, 250); }
    inline void setRefran(const char *refran) { strncpy(refran_, refran, 250); }
    inline void setRefranOculto(const char *refranOculto) { strncpy(refranOculto_, refranOculto, 250); }
    inline void setRefranOculto(char *refranOculto) { strncpy(refranOculto_, refranOculto, 250); }

    void getRandomRefran();
    void hideRefran(const char *refran);

    bool solveRefran(const char *refran);

    int findOcurrences(const char letter);
};

#endif