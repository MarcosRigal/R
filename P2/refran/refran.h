#ifndef REFRAN_H
#define REFRAN_H
#include <cstring>

using namespace std;

class Refran
{
private:
    char refran_[250];
    char refranOculto_[250];

public:
    Refran();

    inline char *getRefran() { return refran_; }
    inline char *getRefranOculto() { return refranOculto_; }

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