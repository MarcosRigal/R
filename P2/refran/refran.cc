#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "refran.h"
using namespace std;

Refran::Refran()
{
    getRandomRefran();
    hideRefran(refran_);
}

void Refran::getRandomRefran()
{
    srand(time(NULL));
    int nrand = (rand() % 5) + 1;
    //int nrand = 5;
    switch (nrand)
    {
    case 1:
        sprintf(refran_, "Para todos sale el sol.");
        break;
    case 2:
        sprintf(refran_, "Cuando el invierno es lluvioso, el verano es abundoso.");
        break;
    case 3:
        sprintf(refran_, "Mes de flores, mes de amores.");
        break;
    case 4:
        sprintf(refran_, "Lo mejor de las cartas es no jugarlas.");
        break;
    case 5:
        sprintf(refran_, "Marzo lluvioso, mayo copioso.");
        break;
    default:
        break;
    }
}

void Refran::hideRefran(const char *refran)
{
    strcpy(refranOculto_, refran);
    for (int i = 0; refran[i] != '.'; i++)
    {
        if (refran[i] != '\0' && refran[i] != ' ' && refran[i] != '.' && refran[i] != ',' && refran[i] != ';' && refran[i] != '¡' && refran[i] != '!' && refran[i] != '¿' && refran[i] != '?' && refran[i] != ':')
        {
            refranOculto_[i] = '_';
        }
        else
        {
            refranOculto_[i] = refran_[i];
        }
    }
}

bool Refran::solveRefran(const char *refran)
{
    char copyRefran[250];
    strcpy(copyRefran, refran);
    strtok(copyRefran, "\n");
    int i = 0;
    while (refran_[i] != '.')
    {
        if (toupper(refran_[i]) != toupper(copyRefran[i]))
        {
            return false;
        }

        i++;
    }
    return true;
}

int Refran::findOcurrences(const char letter)
{
    int i, count;
    count = 0;
    i = 0;
    while (refran_[i] != '.')
    {
        if (toupper(refran_[i]) == toupper(letter))
        {
            count++;
            refranOculto_[i] = refran_[i];
        }

        i++;
    }

    return count;
}

bool Refran::hasBeenShown(const char letter)
{
    int i;
    i = 0;
    while (refranOculto_[i] != '.')
    {
        if (toupper(refranOculto_[i]) == toupper(letter))
        {
            return true;
        }

        i++;
    }

    return false;
}