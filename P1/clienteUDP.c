#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

/* --------------------------------------------------------------------------------------
 
 Env�a un n�mero aleatorio al servidor, quien el devuelve el n�mero incrementado

---------------------------------------------------------------------------------------- */

int main(int argc, char const *argv[])
{

	/*---------------------------------------------------- 
			Descriptor del socket y buffer para datos 
		-----------------------------------------------------*/
	int Socket_Cliente;
	char Cadena[256];

	/* -----------------------------------------------------
   		Informaci\ufffdn del Servidor
   	-----------------------------------------------------*/
	struct sockaddr_in Servidor;
	socklen_t Longitud_Servidor;

	/* --------------------------------------------------
			Se abre el socket cliente
		---------------------------------------------------*/
	Socket_Cliente = socket(AF_INET, SOCK_DGRAM, 0);
	if (Socket_Cliente == -1)
	{
		printf("No se puede abrir el socket cliente\n");
		exit(-1);
	}

	/*---------------------------------------------------------------------
			Necesitamos una estructura con la informaci\ufffdn del Servidor
			para poder solicitarle un servicio.
   		----------------------------------------------------------------------*/
	Servidor.sin_family = AF_INET;
	Servidor.sin_port = htons(2000);
	Servidor.sin_addr.s_addr = inet_addr(argv[1]);
	Longitud_Servidor = sizeof(Servidor);

	/*------------------------------------------------------------------------
			Se genera un n\ufffdmero aleatorio, que es el que se le manda al
			servidor.
		------------------------------------------------------------------------ */
	srand(time(NULL));	 /* Semilla para n\ufffdmeros aleatorios */
	scanf("%s", Cadena); /* Aleatorio entre 0 y 19 */
	printf("Envio %s\n", Cadena);

	/*-----------------------------------------------------------------------
			Se env\ufffda mensaje al Servidor
		-----------------------------------------------------------------------*/
	for (size_t i = 0; i < 3; i++)
	{
		int enviado = sendto(Socket_Cliente, (char *)&Cadena, sizeof(Cadena), 0, (struct sockaddr *)&Servidor, Longitud_Servidor);
		if (enviado < 0)
		{
			printf("Error al solicitar el servicio\n");
			sleep(atoi(argv[2]));
		}
		else
		{
			/*----------------------------------------------------------------------
			Esperamos la respuesta del Servidor
			----------------------------------------------------------------------- */
			int recibido = recvfrom(Socket_Cliente, (char *)&Cadena, sizeof(Cadena), 0,
									(struct sockaddr *)&Servidor, &Longitud_Servidor);

			if (recibido > 0)
				printf("Leido %s\n", Cadena);
			else
				printf("Error al leer del servidor\n");
		}
	}

	close(Socket_Cliente);

	return 0;
}
