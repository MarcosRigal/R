#include <time.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void tiempo(char *cadena)
{

    time_t tiempo;
    struct tm *stTm;

    tiempo = time(NULL);

    setlocale(LC_ALL, "");

    stTm = localtime(&tiempo);

    if (strcmp(cadena, "DAY") == 0)
    {
        strftime(cadena, 256, "%A, %d de %B", stTm);
    }

    else if (strcmp(cadena, "TIME") == 0)
    {
        strftime(cadena, 256, "%H:%M:%S", stTm);
    }

    else if (strcmp(cadena, "DAYTIME") == 0)
    {
        strftime(cadena, 256, "%A, %d de %B; %H:%M:%S", stTm);
    }
}

int main()
{
    /*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
    int Socket_Servidor;
    struct sockaddr_in Servidor;
    char Cadena[256];

    /* -----------------------------------------------------
   		Informaci\ufffdn del Cliente
   	-----------------------------------------------------*/
    struct sockaddr_in Cliente;
    socklen_t Longitud_Cliente;

    /* --------------------------------------------------
		Se abre el socket Servidor
	---------------------------------------------------*/
    Socket_Servidor = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket_Servidor == -1)
    {
        printf("No se puede abrir socket servidor\n");
        exit(-1);
    }

    /* ------------------------------------------------------------------
		Se rellenan los campos de la estructura servidor, necesaria
		para la llamada a la funcion bind().
	-------------------------------------------------------------------*/
    Servidor.sin_family = AF_INET;
    Servidor.sin_port = htons(2000);
    Servidor.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(Socket_Servidor, (struct sockaddr *)&Servidor, sizeof(Servidor)) == -1)
    {
        close(Socket_Servidor);
        exit(-1);
    }

    /*---------------------------------------------------------------------
		Del cliente s\ufffdlo necesitamos el tama\ufffdo de su estructura, el 
		resto de informaci\ufffdn (familia, puerto, ip), la obtendremos 
		nos la proporcionar\ufffd el propio m\ufffdtodo recvfrom, cuando
		recibamos la llamada de un cliente.
   ----------------------------------------------------------------------*/
    Longitud_Cliente = sizeof(Cliente);

    /*-----------------------------------------------------------------------
		El servidor espera continuamente los mensajes de los clientes
	------------------------------------------------------------------------ */
    while (1)
    {
        /* -----------------------------------------------------------------
			Esperamos la llamada de alg\ufffdn cliente
		-------------------------------------------------------------------*/
        int recibido = recvfrom(Socket_Servidor, (char *)&Cadena, sizeof(Cadena), 0,
                                (struct sockaddr *)&Cliente, &Longitud_Cliente);

        /* -----------------------------------------------------------------
			Comprobamos si hemos recibido alguna informaci\ufffdn 
		-------------------------------------------------------------------*/
        if (recibido > 0)
        {
            printf("Recibido: %s enviando respuesta...\n", Cadena);
            if (strcmp(Cadena, "DAY") == 0 || strcmp(Cadena, "TIME") == 0 || strcmp(Cadena, "DAYTIME") == 0)
            {
                tiempo(Cadena);
            }
            else
            {
                strcpy(Cadena, "Error, no se ha encontrado el servicio solicitado. Los servicios ofrecidos son DAY, TIME y DAYTIME\n");
            }
            /* ------------------------------------------------------------------
				Devolvemos el resultado
				--------------------------------------------------------------------*/
            int enviado = sendto(Socket_Servidor, (char *)&Cadena, sizeof(Cadena), 0,
                                 (struct sockaddr *)&Cliente, Longitud_Cliente);
        }
    }

    close(Socket_Servidor);

    return 0;
}