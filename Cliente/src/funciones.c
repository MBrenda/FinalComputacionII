#include "../include/header.h"

void clean(char * buff) {
	int i;
	for(i = 0; i < strlen(buff); i++){
		buff[i] = '\0';
	}
}

char * ingresarTicket(int op, char id_ticket[]) {

	char *ticket = (char *) malloc (BUF_SIZE * sizeof(char));
	char titulo[20];
	char autor[30];
	char descripcion[100];
	
	printf ("\nTitulo: ");
	fgets(titulo, 20, stdin);
	*(titulo+(strlen(titulo)-1)) = '\0';
	printf ("Autor: ");
	fgets(autor, 30, stdin);
	*(autor+(strlen(autor)-1)) = '\0';
	printf ("Descripcion: ");
	fgets(descripcion, 100, stdin);
	*(descripcion+(strlen(descripcion)-1)) = '\0';
	
	if (op == 'i')
		sprintf (ticket, "%c|%s|%s|%s", op, titulo, autor, descripcion);
	else//si no es la i es la e
		sprintf (ticket, "%c|%s|%s|%s|%s", op, id_ticket, titulo, autor, descripcion);

	return ticket;
}

void listarTickets(char tickets[]) {

	char *token1, *token2;
	char *saveptr1, *saveptr2;

	token1 = strtok_r(tickets, "-", &saveptr1);
   	//cada vez que encutra un | escribe lo que sigue abajo.
	while (token1 != NULL)
	{
		token2 = strtok_r(token1, "|", &saveptr2);	
		
		while (token2 != NULL)
		{
			printf("\n%s", token2);
			token2 = strtok_r(NULL, "|", &saveptr2);
		}

		token1 = strtok_r(NULL, "-", &saveptr1);
	}
}

void error(char error[]) {	
	fprintf(stderr,"%d %s %s\n",errno,error,strerror(errno));
	exit(1);	
}
