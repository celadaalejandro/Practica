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
void recvfrom_socket(int s,struct sockaddr_in* client_address)
{
	//Nos pasan por referencia la direcion de quien nos lo envia
	//(Esta vacia inicialmente)
        char  mens_serv[20];
	int size_client_address = sizeof(*client_address);
	printf(">>> Esperando a recibir datos");
        int num_byte_received = recvfrom(s,mens_serv,sizeof(mens_serv),0,(struct sockaddr *) &client_address,&size_client_address);
        if(num_byte_received < 0)
        {
                perror("Eror al RECIBIR los datos del cliente");
                printf("El numero de byte recibido es: %d \n\n",num_byte_received);
                exit(0);
        }
        else
        {	
		
                printf("Se han RECIBIDO %d bytes de: \n",num_byte_received);
                printf("        IP: %s \n\n",inet_ntoa(client_address->sin_addr));
        	printf("        Protocolo: %hi \n",client_address->sin_family);
        	printf("        Puerto: %hi \n\n",ntohs(client_address->sin_port));
		printf("----------El dato recibido es----------:\n");
		printf("%s\n\n\n",mens_serv);
        }
}
void sendto_socket(int s, struct sockaddr_in* sent_address)
{
	//Nos pasan por referencia la direcion de a quien queremos  enviar
        // la informacion (Esta rrellenada ya inicialmente)
        char message_to_send[20]="Primer mensaje";
	int size=sizeof((struct sockaddr *)sent_address);
	int num_byte_received = sendto(s,message_to_send,sizeof(message_to_send),0,(struct sockaddr *) &sent_address,size);
	if(num_byte_received < 0)
        {
                perror("Eror al ENVIAR los datos del cliente");
                exit(0);
        }
        else
        {
                printf("Se han ENVIADO %d  bytes a: \n\n",(int)sizeof(message_to_send));
                printf("        IP: %s \n\n",inet_ntoa(sent_address->sin_addr));
                printf("        Protocolo: %hi \n",sent_address->sin_family);
                printf("        Puerto: %hi \n\n",ntohs(sent_address->sin_port));
                printf("----------El dato ENVIADO es----------:\n");
                printf("%s\n\n\n",message_to_send);

        }
}
int  open_socket()
{
        //Parametros PF_INET(IPV4),SOCK_DGRAM(UDP)
        int s;
        if((s=socket(PF_INET,SOCK_DGRAM,0))<0)
        {
                perror("Eror en la creación del socket.\n");
                exit(0);
        }
        else
        {
                printf("Se ha CREADO correctamente el socket. ");
                printf("El valor del socket es %d.\n",s);
                return s;
        }
}
int closed_socket(int s)
{
        if(close(s)<0)
        {
                perror("Eror al cerrar el socket.\n");
                exit(0);
        }
        else
        {
                printf("Se ha CERRADO correctamente el socket. ");
                printf("El valor del socket es  %d.\n",s);
                return s;
        }
}
int bind_socket(int s, struct sockaddr_in* my_address, int PORT)
{
        //Rellenamos la estructura que recoge los datos del servidor
        bzero(my_address->sin_zero,8);
        my_address->sin_family = AF_INET;
        my_address->sin_port = htons(PORT);
	//INADDR_ANY
        my_address->sin_addr.s_addr =inet_addr(INADDR_ANY);
        
	int aux_num_socket = bind(s,(struct sockaddr*) my_address,sizeof(*my_address));
        if(aux_num_socket==(-1))
      	{
                perror("Eror al ENLAZAR los datos  al socket.\n");
                exit(0);
        }
        else
        {
                printf("Se han ENLAZADO correctamente los datos  al socket. ");
                printf("El valor del socket es  %d.\n",s);
                return aux_num_socket;
        }
}

