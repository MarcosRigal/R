#include <stdlib.h>
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
