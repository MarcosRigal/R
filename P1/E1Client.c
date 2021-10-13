#include <time.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    /*
        Aquí compruebo que el programa se ha llamado correctamente
    */
    if (argc < 3)
    {
        printf("Error:Too few arguments\n");
        printf("Call the program by this way:\n");
        printf("./E1Client <Server's Ip> <Response TimeOut>\n");
        return -1;
    }
    /*
        La estructura timeval timeout nos permite controlar el tiempo que va a esperar select
    */
    struct timeval timeout;
    /*
        Conjunto de sockets que serán comprobados para ver si existen caracteres para leer
    */
    fd_set readfds;
    /*
        Variable que almacenará el retorno del select
    */
    int selectReturn;

    /*
        timeout.tv_sec = Tiempo de espera en segundos
        timeout.tv_usec = Tiempo de espera en microsegundos
    */
    timeout.tv_sec = atoi(argv[2]);
    timeout.tv_usec = 0;

    /* 
		Descriptor del socket y buffer para datos 
    */
    int Socket_Cliente;
    int Datos;

    /*
   		Información del Servidor
   	*/
    struct sockaddr_in Servidor;
    socklen_t Longitud_Servidor;

    /*
	    Se abre el socket cliente
	*/
    Socket_Cliente = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket_Cliente == -1)
    {
        printf("No se puede abrir el socket cliente\n");
        exit(-1);
    }

    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(Socket_Cliente, &readfds);

    /*
		Necesitamos una estructura con la información del Servidor
		para poder solicitarle un servicio.
   	*/

    Servidor.sin_family = AF_INET;
    Servidor.sin_port = htons(2000);
    Servidor.sin_addr.s_addr = inet_addr(argv[1]);
    Longitud_Servidor = sizeof(Servidor);

    /*
		Se genera un número aleatorio, que es el que se le manda al
		servidor.
	*/
    srand(time(NULL));   /* Semilla para números aleatorios */
    Datos = rand() % 20; /* Aleatorio entre 0 y 19 */
    printf("Envio %d\n", Datos);

    /*
		Se envía mensaje al Servidor
	*/

    int enviado = sendto(Socket_Cliente, (char *)&Datos, sizeof(Datos), 0,
                         (struct sockaddr *)&Servidor, Longitud_Servidor);

    if (enviado < 0)
    {
        printf("Error al solicitar el servicio\n");
    }

    for (int i = 0; (i < 3); i++)
    {
        selectReturn = select(2, &readfds, NULL, NULL, &timeout);
        if (selectReturn == -1)
        {
            printf("Se ha producido un error en select\n");
        }
        else if (selectReturn == 0)
        {
            printf("Se ha agotado el tiempo\n");
            int enviado = sendto(Socket_Cliente, (char *)&Datos, sizeof(Datos), 0,
                                 (struct sockaddr *)&Servidor, Longitud_Servidor);

            if (enviado < 0)
            {
                printf("Error al solicitar el servicio\n");
            }
            timeout.tv_sec = atoi(argv[2]);
            timeout.tv_usec = 0;
            FD_ZERO(&readfds);
            FD_SET(0, &readfds);
            FD_SET(Socket_Cliente, &readfds);
        }
        else
        {
            /*
			Esperamos la respuesta del Servidor
			*/
            int recibido = recvfrom(Socket_Cliente, (char *)&Datos, sizeof(Datos), 0,
                                    (struct sockaddr *)&Servidor, &Longitud_Servidor);

            if (recibido > 0)
                printf("Leido %d\n", Datos);
            else
                printf("Error al leer del servidor\n");

            close(Socket_Cliente);
            i = 3;
        }
    }

    return 0;
}
