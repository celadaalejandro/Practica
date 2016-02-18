#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //close()
#include <string.h> //strlen
#include <stdlib.h> //system("clear")

int main (int argc, char *argv[])
{
	system("clear");
	if(argc!=3)
	{
		printf("ERROR:USO INCORRECTO DEL PROGRAMA ES: ping_noc.c IP PUERTO %d\n",argc);
		exit(1);
	}
	char message[]="No gods or kings";//server_reply[2000];
	int fd;
	//Creamos el socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)		
	{
		perror("cannot create socket");
		return 0;
	}
	//Estructura que nos identifica
	struct sockaddr_in client;				
	//Rellenamos los datos que identificaran al servidor	
	memset((char *)&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	client.sin_port = htons(0);
		
	if (bind(fd, (struct sockaddr *)&client, sizeof(client)) < 0)
	{
		perror("No se ha podido enlazar el socket");
		return 0;
	}
	//Estructura que identificara al server
	struct sockaddr_in server;
	//Rellenamos los datos que identificaran al servidor	
	memset((char*)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	client.sin_addr.s_addr = inet_addr(argv[1]);
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
	/*

	//Recibir mensaje de respuesta
	if(recv(socket_desc, server_reply, 2000, 0) < 0)
	{
		puts("Recepcion fallida");
	}
	puts("Mensaje recibido\n");
	puts(server_reply);
	
	*/
	//Cerrar el socket una vez enviado el mensaje
	close(fd);
	return 0;
}

