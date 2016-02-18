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
#define PORT 0

int main()
{
        system("clear");
        //Definimos las variables
        int num_socket;
        struct sockaddr_in my_address, server_address;
        num_socket=open_socket();                       //Cremaos el socket.
        bind_socket(num_socket,&my_address,PORT);       //Enlazamos los datos al socket(IP,Puerto,...)

	bzero(my_address.sin_zero,8);
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(5000);
        server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	//htonl
	//printf("%lu\n",htonl("192.168.47.130"));
	//for(;;)
        //{
                sendto_socket(num_socket,&server_address);            //Enviamos los datos 
		//recvfrom_socket(num_socket,&server_address);//Ponemos al socket a la escucha
        //}
        closed_socket(num_socket);                      //Cerrar el socket.
        return 0;
}

