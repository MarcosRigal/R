#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "systemFunctions.h"

using namespace std;

void clear()
{ //Funcion que limpia la terminal en función del sistema operativo que estemos utilizando
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
}

void saveSystem()
{
}

void loadSystem()
{
   GameManager *gameManager = GameManager::getInstance();
   FILE *f;
   f = fopen("users.txt", "r");
   if (!f)
   {
      std::cout << "Error al abrir el archivo\n";
      EXIT_FAILURE;
   }
   char cadena[512];
   while (fgets(cadena, 512, f) != NULL)
   {
      User user;
      char *aux;
      aux = strtok(cadena, ",");
      user.setUserName(aux);
      aux = strtok(NULL, "\n");
      user.setUserPassword(aux);
      gameManager->addUser(user);
   }
   fclose(f);
}