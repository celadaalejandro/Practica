#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //close()
#include <string.h> //strlen
#include <stdlib.h> //system("clear")

int main (int argc, char *argv[])
{
	system("clear");
	if(argc!=2)
	{
		printf("ERROR:USO INCORRECTO DEL PROGRAMA ES: PUERTO %d\n",argc);
		exit(1);
	}
	//char message[]="No gods or kings";//server_reply[2000];
	int fd;
	//Creamos el socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)		
	{
		perror("cannot create socket");
		return 0;
	}
	//Estructura que nos identifica
	struct sockaddr_in server;				
	//Rellenamos los datos que identificaran al servidor	
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(atoi(argv[1]));
		
	if (bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("No se ha podido enlazar el socket");
		return 0;
	}
	while(1)
	{
		//Estructura que identificara a los clientes
		struct sockaddr_in client;
		int size_message;
		char datos[255];
		int size_client = sizeof(client);
		//Recibir mensaje de respuesta
		if((size_message = recvfrom(fd,datos,sizeof(datos),0,(struct sockaddr *)&client,(int *)&size_client))==-1)
		{
			perror("No se ha podido enlazar el socket");
			return 0;
		}
		else if (size_message==0)
		{
			printf("Se ha recibido 0 bytes. Cerramos el servidor.");
			return 0;
		}
		else
		{
			printf(">>>Se ha recibido de la IP %s mediante el puerto %d  %d bytes\n",inet_ntoa(client.sin_addr),server.sin_port,size_message);
			printf("El mensaje recibido ha sido: %s\n",datos);
		}

	
		
		//Cerrar el socket una vez enviado el mensaje
		/*
		//Enviamos el ping
		if (sendto(fd, message, strlen(message), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		{
			perror("sendto failed");
			return 0;
		}
		else
		{
			printf(">>>Se ha enviado a la IP %s mediante el puerto %d : %s \n",inet_ntoa(client.sin_addr),server.sin_port,message);
		}
		*/

		close(fd);
	}
	return 0;
}
