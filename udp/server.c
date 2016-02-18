/*
			 _   _          _          _   _
			| | | |        / \        | | | |
			| | | |       / _ \       | |_| |
			| |_| |  _   / ___ \   _  |  _  |
			 \___/  (_) /_/   \_\ (_) |_| |_|


*/
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h> 
#include<arpa/inet.h>
#include"socket.h"
#define PORT 5000 
int main()
{
	system("clear");
	//Definimos las variables
	int num_socket;
	struct sockaddr_in my_address, client_address;
	num_socket=open_socket();			//Cremaos el socket.
	bind_socket(num_socket,&my_address,PORT);	//Enlazamos los datos al socket(IP,Puerto,...)
	for(;;)
	{
		recvfrom_socket(num_socket,&client_address);//Ponemos al socket a la escucha
		sendto_socket(num_socket,&client_address);		//Enviamos los datos al cliente
	}
	closed_socket(num_socket);			//Cerrar el socket.
	return 0;
}
