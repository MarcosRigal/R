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

#define MSG_SIZE 350
#define MAX_CLIENTS 30

/*
 * El servidor ofrece el servicio de un chat
 */

void exitHandler(int signum);
void salirCliente(int socket, fd_set *readfds, int *numClientes, int arrayClientes[]);

/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
int Server_Socket, New_Server_Socket;
struct sockaddr_in sockname, from;
char buffer[MSG_SIZE];
socklen_t from_len;
fd_set readfds, auxfds;
int salida;
int arrayClientes[MAX_CLIENTS];
int numClientes = 0;
//contadores
int i, j, k;
int recibidos;
char identificador[MSG_SIZE];

int on, ret;

int main()
{

   /* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
   Server_Socket = socket(AF_INET, SOCK_STREAM, 0);
   if (Server_Socket == -1)
   {
      perror("No se puede abrir el socket cliente\n");
      exit(1);
   }

   // Activaremos una propiedad del socket para permitir· que otros
   // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
   // Esto permite· en protocolos como el TCP, poder ejecutar un
   // mismo programa varias veces seguidas y enlazarlo siempre al
   // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
   // quedase disponible (TIME_WAIT en el caso de TCP)
   on = 1;
   ret = setsockopt(Server_Socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2050);
   sockname.sin_addr.s_addr = INADDR_ANY;

   if (bind(Server_Socket, (struct sockaddr *)&sockname, sizeof(sockname)) == -1)
   {
      perror("Error en la operación bind");
      exit(1);
   }

   /*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
   from_len = sizeof(from);

   if (listen(Server_Socket, 1) == -1)
   {
      perror("Error en la operación de listen");
      exit(1);
   }

   //Inicializar los conjuntos fd_set
   FD_ZERO(&readfds);
   FD_ZERO(&auxfds);
   FD_SET(Server_Socket, &readfds);
   FD_SET(0, &readfds);

   //Capturamos la señal SIGINT (Ctrl+c)
   signal(SIGINT, exitHandler);

   /*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
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
                     perror("Error aceptando peticiones");
                  }
                  else
                  {
                     if (numClientes < MAX_CLIENTS)
                     {
                        arrayClientes[numClientes] = New_Server_Socket;
                        numClientes++;
                        FD_SET(New_Server_Socket, &readfds);

                        strcpy(buffer, "Bienvenido al chat\n");

                        send(New_Server_Socket, buffer, sizeof(buffer), 0);

                        for (j = 0; j < (numClientes - 1); j++)
                        {

                           bzero(buffer, sizeof(buffer));
                           sprintf(buffer, "Nuevo Cliente conectado: %d\n", New_Server_Socket);
                           send(arrayClientes[j], buffer, sizeof(buffer), 0);
                        }
                     }
                     else
                     {
                        bzero(buffer, sizeof(buffer));
                        strcpy(buffer, "Demasiados clientes conectados\n");
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

                        salirCliente(i, &readfds, &numClientes, arrayClientes);
                     }
                     else
                     {

                        snprintf(identificador, (sizeof(buffer) + 6), "<%d>: %s", i, buffer);
                        bzero(buffer, sizeof(buffer));

                        strcpy(buffer, identificador);

                        printf("%s\n", buffer);

                        for (j = 0; j < numClientes; j++)
                           if (arrayClientes[j] != i)
                              send(arrayClientes[j], buffer, sizeof(buffer), 0);
                     }
                  }
                  //Si el cliente introdujo ctrl+c
                  if (recibidos == 0)
                  {
                     printf("El socket %d, ha introducido ctrl+c\n", i);
                     //Eliminar ese socket
                     salirCliente(i, &readfds, &numClientes, arrayClientes);
                  }
               }
            }
         }
      }
   }

   close(Server_Socket);
   return 0;
}

void salirCliente(int socket, fd_set *readfds, int *numClientes, int arrayClientes[])
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

   bzero(buffer, sizeof(buffer));
   sprintf(buffer, "Desconexión del cliente: %d\n", socket);

   for (j = 0; j < (*numClientes); j++)
      if (arrayClientes[j] != socket)
         send(arrayClientes[j], buffer, sizeof(buffer), 0);
}

void exitHandler(int signum)
{
   printf("\nApagando el servidor...\n");
   signal(SIGINT, exitHandler);
   for (j = 0; j < numClientes; j++)
   {
      bzero(buffer, sizeof(buffer));
      strcpy(buffer, "Desconectado por el servidor\n");
      send(arrayClientes[j], buffer, sizeof(buffer), 0);
      close(arrayClientes[j]);
      FD_CLR(arrayClientes[j], &readfds);
   }
   close(Server_Socket);
   exit(-1);
}
