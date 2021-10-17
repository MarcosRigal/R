#include "../P2/systemFunctions/systemFunctions.h"
#include "../P2/gameManager/gameManager.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define MSG_SIZE 350
#define MAX_CLIENTS 30

/*
 * El servidor ofrece el servicio de un chat
 */

void exitHandler(int signum);
void closedClient(int socket, fd_set *readfds, int *numClientes, int arrayClientes[]);

/* 
	Inicializamos las variables del programa                
*/
int Server_Socket, New_Server_Socket;
struct sockaddr_in sockname, from;
char buffer[MSG_SIZE];
socklen_t from_len;
fd_set readfds, auxfds;
int salida;
int arrayClientes[MAX_CLIENTS];
int numClientes = 0;
int i, j, k;
int recibidos;
char identificador[MSG_SIZE];

int on, ret;

GameManager *gameManager = GameManager::getInstance();

int main()
{
   loadSystem();
   /*
      Incializamos los sockets y preparamos el servidor para la lectura
   */

   Server_Socket = socket(AF_INET, SOCK_STREAM, 0);
   if (Server_Socket == -1)
   {
      perror("–ERR. No se puede abrir el socket cliente\n");
      exit(1);
   }

   on = 1;
   ret = setsockopt(Server_Socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2050);
   sockname.sin_addr.s_addr = INADDR_ANY;

   if (bind(Server_Socket, (struct sockaddr *)&sockname, sizeof(sockname)) == -1)
   {
      perror("–ERR. No se ha podido realizar la operación bind");
      exit(1);
   }

   from_len = sizeof(from);

   if (listen(Server_Socket, 1) == -1)
   {
      perror("–ERR. No se ha podido realizar la operación listen");
      exit(1);
   }

   FD_ZERO(&readfds);
   FD_ZERO(&auxfds);
   FD_SET(Server_Socket, &readfds);
   FD_SET(0, &readfds);

   signal(SIGINT, exitHandler);

   while (1)
   {

      //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

      auxfds = readfds;

      salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

      if (salida > 0)
      {

         for (i = 0; i < FD_SETSIZE; i++)
         {

            //Buscamos el socket por el que se ha establecido la comunicación
            if (FD_ISSET(i, &auxfds))
            {

               if (i == Server_Socket)
               {

                  if ((New_Server_Socket = accept(Server_Socket, (struct sockaddr *)&from, &from_len)) == -1)
                  {
                     perror("–ERR. No se han podido aceptar peticiones");
                  }
                  else
                  {
                     if (numClientes < MAX_CLIENTS)
                     {
                        arrayClientes[numClientes] = New_Server_Socket;
                        numClientes++;
                        FD_SET(New_Server_Socket, &readfds);

                        strcpy(buffer, "+Ok. Usuario conectado\n");

                        send(New_Server_Socket, buffer, sizeof(buffer), 0);

                        if (gameManager->matchUser(New_Server_Socket))
                        {
                           strcpy(buffer, "+Ok. Empieza la partida. FRASE: _ _ _ _ _ _ _ _ _ _ _ _\n");
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                        }
                        else
                        {
                           strcpy(buffer, "+Ok. Petición Recibida.Quedamos a la espera de más jugadores\n");
                        }
                        send(New_Server_Socket, buffer, sizeof(buffer), 0);
                     }

                     /*
                        Esta parte informa a los clientes de que se ha conectado alguién

                        for (j = 0; j < (numClientes - 1); j++)
                        {

                           bzero(buffer, sizeof(buffer));
                           sprintf(buffer, "Nuevo Cliente conectado: %d\n", New_Server_Socket);
                           send(arrayClientes[j], buffer, sizeof(buffer), 0);
                        }
                  
                        */
                     else
                     {
                        bzero(buffer, sizeof(buffer));
                        strcpy(buffer, "–ERR. Demasiados clientes conectados\n");
                        send(New_Server_Socket, buffer, sizeof(buffer), 0);
                        close(New_Server_Socket);
                     }
                  }
               }
               else if (i == 0)
               {
                  //Se ha introducido información de teclado
                  bzero(buffer, sizeof(buffer));
                  fgets(buffer, sizeof(buffer), stdin);

                  //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                  if (strcmp(buffer, "SALIR\n") == 0)
                  {
                     exitHandler(SIGINT);
                  }
                  //Mensajes que se quieran mandar a los clientes (implementar)
               }
               else
               {
                  bzero(buffer, sizeof(buffer));

                  recibidos = recv(i, buffer, sizeof(buffer), 0);

                  if (recibidos > 0)
                  {

                     if (strcmp(buffer, "SALIR\n") == 0)
                     {

                        closedClient(i, &readfds, &numClientes, arrayClientes);
                     }
                     else
                     {
                        //Esta parte envía el mensaje al otro
                        snprintf(identificador, (sizeof(buffer) + 6), "<%d>: %s", i, buffer);
                        bzero(buffer, sizeof(buffer));

                        strcpy(buffer, identificador);

                        printf("%s to %d\n", buffer, gameManager->findPair(i));

                        send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                     }
                  }
                  //Si el cliente introdujo ctrl+c
                  if (recibidos == 0)
                  {
                     printf("El socket %d, ha introducido ctrl+c\n", i);
                     //Eliminar ese socket
                     closedClient(i, &readfds, &numClientes, arrayClientes);
                  }
               }
            }
         }
      }
   }

   close(Server_Socket);
   return 0;
}

void closedClient(int socket, fd_set *readfds, int *numClientes, int arrayClientes[])
{

   char buffer[250];
   int j;

   close(socket);
   FD_CLR(socket, readfds);

   //Re-estructurar el array de clientes
   for (j = 0; j < (*numClientes) - 1; j++)
      if (arrayClientes[j] == socket)
         break;
   for (; j < (*numClientes) - 1; j++)
      (arrayClientes[j] = arrayClientes[j + 1]);

   (*numClientes)--;
   /*
   Informa al resto de clientes de que alguien se ha desconectado
   bzero(buffer, sizeof(buffer));
   sprintf(buffer, "Desconexión del cliente: %d\n", socket);

   for (j = 0; j < (*numClientes); j++)
      if (arrayClientes[j] != socket)
         send(arrayClientes[j], buffer, sizeof(buffer), 0);
   */
}

void exitHandler(int signum)
{
   printf("\nApagando el servidor...\n");
   signal(SIGINT, exitHandler);
   for (j = 0; j < numClientes; j++)
   {
      bzero(buffer, sizeof(buffer));
      strcpy(buffer, "–ERR. Desconectado por el servidor\n");
      send(arrayClientes[j], buffer, sizeof(buffer), 0);
      close(arrayClientes[j]);
      FD_CLR(arrayClientes[j], &readfds);
   }
   close(Server_Socket);
   saveSystem();
   exit(-1);
}
