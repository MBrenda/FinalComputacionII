#include "../include/header.h"


int main(int argc, char** argv) {

    int sockid, conn_sock, count, c;
    struct sockaddr_in direccion;
    char buffer[BUF_SIZE];

    if((sockid=socket(PF_INET,SOCK_STREAM,0)) < 0) {
        error("socket");
    }

    direccion.sin_family=AF_INET; //address family
    direccion.sin_port=htons(atoi(*(argv+2)));
    direccion.sin_addr.s_addr=inet_addr(*(argv+1));

    if (connect(sockid, (struct sockaddr *)&direccion, sizeof(direccion)) < 0) {
        error("connect");
    }

    c = getopt (argc, argv, "ile:"); //toma los argumentos requeridos. Manera elegante de parcear los argumentos
    printf("Bienvenido!\n");

	switch (c)
	{
		case 'i':
			strcpy(buffer, ingresarTicket(c, NULL));
			count = strlen(buffer);

			if ((send(sockid, buffer, count, 0)) < 0) {
				error("send");
			}
			
			printf("\nTicket ingresado.\n");
		break;
		
		case 'l':
			sprintf (buffer, "%c", c);
			count = strlen(buffer);

			if ((send(sockid, buffer, count, 0)) < 0) {
				error("send");
			}

			recv(sockid, buffer, BUF_SIZE, 0);
			if (count < 0) {
                error("recv");
            }

			listarTickets(buffer);
		break;

		case 'e':
			strcpy(buffer, ingresarTicket(c, argv[4]));
			count = strlen(buffer);

			if ((send(sockid, buffer, count, 0)) < 0) {
				error("send");
			}

			printf("\nTicket editado.\n");
		break;

		default:
			printf("\nOpcion no valida.\n");
			printf("\nIngrese: %s + <-i:insertar, -l:listar, -e:editar>\n", argv[0]);
			error("invalid option");
		break;
	}

    close(sockid);

    return 0;
}
