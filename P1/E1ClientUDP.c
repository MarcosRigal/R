#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
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
        timeout.tv_sec = Tiempo de espera en segundos
        timeout.tv_usec = Tiempo de espera en microsegundos
    */

    timeout.tv_sec = atoi(argv[2]);
    timeout.tv_usec = 0;

    /* 
		Descriptor del socket 
    */

    int Socket_Cliente;

    /*
	    Se abre el socket cliente
	*/

    Socket_Cliente = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket_Cliente == -1)
    {
        printf("No se puede abrir el socket cliente\n");
        exit(-1);
    }

    /*
        Conjunto de sockets que serán comprobados para ver si existen caracteres para leer
    */

    fd_set readfds;

    /*
        Inicializar los conjuntos fd_set
    */

    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(Socket_Cliente, &readfds);

    /*
   		Información del Servidor
   	*/

    struct sockaddr_in Servidor;
    socklen_t Longitud_Servidor;

    /*
		Necesitamos una estructura con la información del Servidor
		para poder solicitarle un servicio.
   	*/

    Servidor.sin_family = AF_INET;
    Servidor.sin_port = htons(2000);
    Servidor.sin_addr.s_addr = inet_addr(argv[1]);
    Longitud_Servidor = sizeof(Servidor);

    /*
    Parte a cambiar para que envie una cadena
    /////////////////////////////////////////////////////////
    */
    int Datos;
    srand(time(NULL));
    Datos = rand() % 20;
    printf("Envio %d\n", Datos);

    ////////////////////////////////////////////////////////

    /*
        Inicializamos la variable para controlar lo que nos devuelva el select 
    */

    int selectReturn = 0;

    for (int i = 0; ((i < 3) && (selectReturn < 1)); i++)
    {
        /*
		    Se envía mensaje al Servidor
	    */
        int enviado = sendto(Socket_Cliente, (char *)&Datos, sizeof(Datos), 0,
                             (struct sockaddr *)&Servidor, Longitud_Servidor);

        /*
		    Se comprueba que se haya enviado bien
	    */

        if (enviado < 0)
        {
            printf("Error al solicitar el servicio\n");
        }

        /*
		    Llamamos a select para esperar la respuesta del sevidor
	    */

        selectReturn = select(Socket_Cliente + 1, &readfds, NULL, NULL, &timeout);

        if (selectReturn == -1)
        {
            printf("Se ha producido un error en select\n");
        }

        else if (selectReturn == 0)
        {
            printf("Se ha agotado el tiempo\n");
            printf("Volviendo a solicitar el servicio\n");

            timeout.tv_sec = atoi(argv[2]);
            timeout.tv_usec = 0;
            FD_ZERO(&readfds);
            FD_SET(0, &readfds);
            FD_SET(Socket_Cliente, &readfds);

            int enviado = sendto(Socket_Cliente, (char *)&Datos, sizeof(Datos), 0,
                                 (struct sockaddr *)&Servidor, Longitud_Servidor);
        }

        else
        {
            int recibido = recvfrom(Socket_Cliente, (char *)&Datos, sizeof(Datos), 0,
                                    (struct sockaddr *)&Servidor, &Longitud_Servidor);

            if (recibido > 0)
                printf("Leido %d\n", Datos);
            else
                printf("Error al leer del servidor\n");

            close(Socket_Cliente);
        }
    }

    return 0;
}
