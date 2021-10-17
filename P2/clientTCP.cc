#include "../P2/systemFunctions/systemFunctions.h"

using namespace std;

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

bool user = false;
bool password = false;
bool playing = false;

int main()
{

   /*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
   int sd;
   struct sockaddr_in sockname;
   char buffer[250];
   socklen_t len_sockname;
   fd_set readfds, auxfds;
   int salida;
   int fin = 0;

   /* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
   sd = socket(AF_INET, SOCK_STREAM, 0);
   if (sd == -1)
   {
      perror("–ERR. No se puede abrir el socket cliente\n");
      exit(1);
   }

   /* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2050);
   sockname.sin_addr.s_addr = inet_addr("127.0.0.1");

   /* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
   len_sockname = sizeof(sockname);

   if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
   {
      perror("–ERR. Al establecer la conexión");
      exit(1);
   }

   //Inicializamos las estructuras
   FD_ZERO(&auxfds);
   FD_ZERO(&readfds);

   FD_SET(0, &readfds);
   FD_SET(sd, &readfds);

   /* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/
   do
   {
      auxfds = readfds;
      salida = select(sd + 1, &auxfds, NULL, NULL, NULL);

      //Tengo mensaje desde el servidor
      if (FD_ISSET(sd, &auxfds))
      {

         bzero(buffer, sizeof(buffer));
         recv(sd, buffer, sizeof(buffer), 0);

         printf("%s", buffer);

         if (strcmp(buffer, "–ERR. Demasiados clientes conectados\n") == 0)
            fin = 1;

         if (strcmp(buffer, "–ERR. Desconectado por el servidor\n") == 0)
            fin = 1;
         if (strcmp(buffer, "+Ok. Usuario correcto\n") == 0)
            user = true;
         if (strcmp(buffer, "+Ok. Usuario validado\n") == 0)
            password = true;
         if (strncmp(buffer, "+Ok. Empieza la partida.", strlen("+Ok. Empieza la partida.")) == 0)
            playing = true;
         if (strcmp(buffer, "+Ok. Petición Recibida. quedamos a la espera de más jugadores\n") == 0)
            playing = true;
         if (strcmp(buffer, "+Ok. Ha salido el otro jugador. Finaliza la partida\n") == 0)
            playing = false;
      }
      else
      {

         //He introducido información por teclado
         if (FD_ISSET(0, &auxfds))
         {
            bzero(buffer, sizeof(buffer));

            fgets(buffer, sizeof(buffer), stdin);

            if (strcmp(buffer, "SALIR\n") == 0)
            {
               fin = 1;
            }
            else if ((strncmp(buffer, "PASSWORD", strlen("PASSWORD")) == 0) && (user == false))
            {
               printf("-Err. No puede introducir la contraseña antes que el nombre de usuario\n");
            }
            else if ((strncmp(buffer, "REGISTRO", strlen("REGISTRO")) == 0) && (user == true))
            {
               printf("-Err. Ya ha iniciado sesión\n");
            }
            else if ((strcmp(buffer, "INICIAR-PARTIDA\n") == 0) && (password == false))
            {
               printf("-Err. No puede iniciar partida antes de iniciar sesión\n");
            }
            else if ((strncmp(buffer, "CONSONANTE", strlen("CONSONANTE")) == 0) && (playing == false))
            {
               printf("-Err. Debe estar en una partida para hacer eso\n");
            }
            else if ((strncmp(buffer, "VOCAL", strlen("VOCAL")) == 0) && (playing == false))
            {
               printf("-Err. Debe estar en una partida para hacer eso\n");
            }
            else if ((strncmp(buffer, "RESOLVER", strlen("RESOLVER")) == 0) && (playing == false))
            {
               printf("-Err. Debe estar en una partida para hacer eso\n");
            }
            else if ((strncmp(buffer, "PUNTUACION", strlen("PUNTUACION")) == 0) && (playing == false))
            {
               printf("-Err. Debe estar en una partida para hacer eso\n");
            }
            else
            {
               send(sd, buffer, sizeof(buffer), 0);
            }
         }
      }

   } while (fin == 0);

   close(sd);

   return 0;
}
