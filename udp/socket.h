void recvfrom_socket(int,struct sockaddr_in*);
void  sendto_socket(int,struct sockaddr_in*);
void fill(struct sockaddr_in, int);
int open_socket();
int closed_socket(int);
int bind_socket(int, struct sockaddr_in*, int);

