#include "../P2/systemFunctions/systemFunctions.h"
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
#include <regex.h>

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

regex_t regex;
int result;

GameManager *gameManager = GameManager::getInstance();

int main()
{
   result = regcomp(&regex, "REGISTRO -u \\w* -p \\w*", REG_EXTENDED);
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
                     }
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

                  //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor.
                  if (strcmp(buffer, "SALIR\n") == 0)
                  {
                     exitHandler(SIGINT);
                  }
               }
               else
               {
                  bzero(buffer, sizeof(buffer));

                  recibidos = recv(i, buffer, sizeof(buffer), 0);

                  if (recibidos > 0)
                  {
                     result = regexec(&regex, buffer, 0, NULL, 0);
                     if (strcmp(buffer, "SALIR\n") == 0)
                     {

                        closedClient(i, &readfds, &numClientes, arrayClientes);
                     }
                     else if (!result)
                     {
                        User user;
                        char *aux;
                        const char *name;
                        const char *password;
                        const char *flag;
                        aux = strtok(buffer, " ");
                        aux = strtok(NULL, " ");
                        aux = strtok(NULL, " ");
                        name = aux;
                        aux = strtok(NULL, " ");
                        flag = aux;
                        aux = strtok(NULL, "\n");
                        password = aux;

                        if (gameManager->nameExist(name))
                        {
                           strcpy(buffer, "–Err. Usuario ya registrado\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else
                        {
                           user.setUserName(name);
                           user.setUserPassword(password);
                           gameManager->addUser(user);
                           strcpy(buffer, "+Ok. Usuario registrado\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                     }
                     else if (strncmp(buffer, "USUARIO ", strlen("USUARIO ")) == 0)
                     {
                        if (strncmp(buffer, "USUARIO \n", strlen("USUARIO \n")) == 0)
                        {
                           strcpy(buffer, "-Err. No se ha podido completar el login\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else
                        {
                           char *aux;
                           aux = strtok(buffer, " ");
                           aux = strtok(NULL, "\n");
                           if (gameManager->nameExist(aux))
                           {
                              if (gameManager->logUser(i, aux))
                              {
                                 strcpy(buffer, "+Ok. Usuario correcto\n");
                              }
                              else
                              {
                                 strcpy(buffer, "-Err. No se ha podido completar el login\n");
                              }
                              send(i, buffer, sizeof(buffer), 0);
                           }
                           else
                           {
                              strcpy(buffer, "–Err. Usuario incorrecto\n");
                              send(i, buffer, sizeof(buffer), 0);
                           }
                        }
                     }
                     else if (strncmp(buffer, "PASSWORD ", strlen("PASSWORD ")) == 0)
                     {
                        if (strncmp(buffer, "PASSWORD \n", strlen("PASSWORD \n")) == 0)
                        {
                           strcpy(buffer, "–ERR. Error en la validación\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else
                        {
                           char *aux;
                           aux = strtok(buffer, " ");
                           aux = strtok(NULL, "\n");
                           if (gameManager->checkPassword(i, aux))
                           {
                              strcpy(buffer, "+Ok. Usuario validado\n");
                              send(i, buffer, sizeof(buffer), 0);
                           }
                           else
                           {
                              strcpy(buffer, "–ERR. Error en la validación\n");
                              send(i, buffer, sizeof(buffer), 0);
                           }
                        }
                     }
                     else if (strncmp(buffer, "INICIAR-PARTIDA", strlen("INICIAR-PARTIDA")) == 0)
                     {
                        int status = gameManager->matchUser(i);
                        if (status == 1)
                        {
                           sprintf(buffer, "+Ok. Empieza la partida. FRASE: %s\n", gameManager->getGame(i).getRefran().getRefranOculto());
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else if (status == 0)
                        {
                           strcpy(buffer, "+Ok. Petición Recibida. quedamos a la espera de más jugadores\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }

                        else
                        {
                           strcpy(buffer, "-Err. Todas las salas están llenas vuelva a intentarlo más tarde\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                     }
                     else if (strncmp(buffer, "SALIR", strlen("SALIR")) == 0)
                     {
                        closedClient(i, &readfds, &numClientes, arrayClientes);
                     }

                     else if (strncmp(buffer, "CHAT ", strlen("CHAT ")) == 0)
                     {
                        send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                     }
                     else if (strncmp(buffer, "CONSONANTE ", strlen("CONSONANTE ")) == 0)
                     {
                        const char c = buffer[11];
                        int ocurrences = gameManager->findOcurrences(i, c);
                        if (ocurrences == 0)
                        {
                           sprintf(buffer, "+Ok. %c aparece %d veces. FRASE: %s\n", c, ocurrences, gameManager->getGame(i).getRefran().getRefranOculto());
                           send(i, buffer, sizeof(buffer), 0);
                           sprintf(buffer, "+Ok. Turno de partida\n");
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                           sprintf(buffer, "+Ok. Turno del otro jugador\n");
                           send(i, buffer, sizeof(buffer), 0);
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else
                        {
                           printf("%s\n", gameManager->getGame(i).getRefran().getRefranOculto());
                           gameManager->addPlayerScore(i, ocurrences);
                           sprintf(buffer, "+Ok. %c aparece %d veces. FRASE: %s\n", c, ocurrences, gameManager->getGame(i).getRefran().getRefranOculto());
                           send(i, buffer, sizeof(buffer), 0);
                        }
                     }
                     else if (strncmp(buffer, "VOCAL ", strlen("VOCAL ")) == 0)
                     {
                     }
                     else if (strncmp(buffer, "RESOLVER ", strlen("RESOLVER ")) == 0)
                     {
                        if (strncmp(buffer, "RESOLVER \n", strlen("RESOLVER \n")) == 0)
                        {
                           sprintf(buffer, "+Ok. Partida finalizada. FRASE: %s. No se ha acertado la frase.\n", gameManager->getGame(i).getRefran().getRefran());
                           send(i, buffer, sizeof(buffer), 0);
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                           gameManager->deleteGame(i);
                        }
                        else
                        {
                           char *aux;
                           aux = strtok(buffer, " ");
                           aux = strtok(NULL, "\n");
                           if (gameManager->getGame(i).getRefran().solveRefran(aux))
                           {
                              sprintf(buffer, "+Ok. Partida finalizada. FRASE: %s. Ha ganado el jugador %s con %d puntos\n", gameManager->getGame(i).getRefran().getRefran(), gameManager->getName(i), gameManager->getGame(i).getScore(i));
                              send(i, buffer, sizeof(buffer), 0);
                              send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                              gameManager->deleteGame(i);
                           }
                           else
                           {
                              sprintf(buffer, "+Ok. Partida finalizada. FRASE: %s. No se ha acertado la frase.\n", gameManager->getGame(i).getRefran().getRefran());
                              send(i, buffer, sizeof(buffer), 0);
                              send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                              gameManager->deleteGame(i);
                           }
                        }
                     }

                     else if (strncmp(buffer, "PUNTUACION", strlen("PUNTUACION")) == 0)
                     {
                        sprintf(buffer, "+Ok. Su puntuación es: %d\n", gameManager->getScore(i));
                        send(i, buffer, sizeof(buffer), 0);
                     }
                     else
                     {
                        strcpy(buffer, "--Err. Solicitud rechazada\n");
                        send(i, buffer, sizeof(buffer), 0);
                     }
                  }
                  //Si el cliente introdujo ctrl+c
                  if (recibidos == 0)
                  {
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
   printf("El socket %d, se ha desconectado\n", i);
   char buffer[250];
   int j;
   strcpy(buffer, "+Ok. Desconexión procesada.\n");
   send(i, buffer, sizeof(buffer), 0);
   strcpy(buffer, "+Ok. Ha salido el otro jugador. Finaliza la partida\n");
   send(gameManager->findPair(i), buffer, sizeof(buffer), 0);

   close(socket);
   FD_CLR(socket, readfds);

   //Re-estructurar el array de clientes
   for (j = 0; j < (*numClientes) - 1; j++)
      if (arrayClientes[j] == socket)
         break;
   for (; j < (*numClientes) - 1; j++)
      (arrayClientes[j] = arrayClientes[j + 1]);

   (*numClientes)--;
   gameManager->unlogUser(i);
   gameManager->deleteGame(i);
}

void exitHandler(int signum)
{
   saveSystem();
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
   regfree(&regex);
   exit(-1);
}
