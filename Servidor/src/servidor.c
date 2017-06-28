#include "../include/header.h"
 
int main(int argc, char** argv) {
 
	char ipstr[INET6_ADDRSTRLEN];

    int sockid, conn_sock, count;
    struct sockaddr_in direccion;
    char buffer[BUF_SIZE];
    int pid;
	struct sockaddr_storage client;
	socklen_t addr_size = sizeof(client);

	if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\nUSAGE: <executable> <port>\n");
         exit(1);
     }

    if((sockid=socket(PF_INET,SOCK_STREAM,0)) < 0) {
        error("socket");
    }

    direccion.sin_family=AF_INET;
    direccion.sin_port=htons(atoi(*(argv+1)));
    direccion.sin_addr.s_addr=htonl(INADDR_ANY);

    if((bind(sockid, (struct sockaddr *)&direccion, sizeof(direccion))) < 0){
        error("bind");
    }

    listen(sockid,1);

	key_t key;
	struct sembuf operacion;
	int sem_id;
	
	if((key = ftok("db/tickets.txt", 1)) < 0){
		error("ftok");
		exit(1);
	}

	if ((sem_id = semget(key, 1, IPC_CREAT | 0777)) < 0) {
		error("semget");
		exit(1);
	}

	if((semctl(sem_id, 0, SETVAL, 1)) < 0){
		error("semctl");
	}

    while(conn_sock=accept(sockid,(struct sockaddr *)&client, &addr_size)) {
        if (conn_sock<0) {
                error("accept");
        }

        if (!(pid=fork())) { 
            while(count=recv(conn_sock,buffer,BUF_SIZE,0)) {
                if (count < 0) {
                    error("recv");
                }

				*(buffer+count)='\0';
			
				if (client.ss_family == AF_INET) {
					struct sockaddr_in *s = (struct sockaddr_in *)&client; //creamos un puntero de la estructura sockaddr_in la cual nos ayuda a referenciar los elementos del socket.
					inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);//convierte direcciones de ipv4 e ipv6 en forma binaria y texto.(familia de la direccion, apuntan al que contiene la direccion ipv4, tamaño de ipstr.
				}

				switch(buffer[0]) {
					case 'i':
						guardarTicket(buffer, ipstr);
						break;
					case 'l':
						strcpy(buffer, enviarTickets());
						send(conn_sock, buffer, strlen(buffer),0);
						break;
					case 'e':
						editarTicket(buffer, ipstr);
						break;
					default:
						exit(1);
						break;
				}
				
				registrar(buffer, ipstr);
            }
            close(sockid);
            exit(0);
        }

        printf("Conexion delegada al proceso hijo No. %d\n",pid);
        waitpid(pid,NULL,WNOWAIT);
    }
    return 0;
}
