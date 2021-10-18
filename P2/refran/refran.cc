#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "refran.h"
using namespace std;

Refran::Refran(int userSocket)
{
    userSocket_ = userSocket;
    getRandomRefran();
    hideRefran(refran_);
}

void Refran::getRandomRefran()
{
    srand(time(NULL));
    int nrand = (rand() % 5) + 1;
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
        sprintf(refran_, "Marzo lluvioso, abril copioso.");
        break;
    default:
        break;
    }
}

void Refran::hideRefran(const char *refran)
{
    int coma = ',';
    char *pch;
    char copyRefran[250];
    strcpy(copyRefran, refran);

    pch = strtok(copyRefran, " ");
    while (pch != NULL)
    {
        if (strchr(pch, coma))
        {
            for (size_t i = 0; i < strlen(pch) - 1; i++)
            {
                strcat(refranOculto_, "_");
            }
            strcat(refranOculto_, ",");
        }
        else
        {
            for (size_t i = 0; i < strlen(pch); i++)
            {
                strcat(refranOculto_, "_");
            }
        }

        pch = strtok(NULL, " .");
        if (pch != NULL)
        {
            strcat(refranOculto_, " ");
        }
        else
        {
            strcat(refranOculto_, ".");
        }
    }
}
