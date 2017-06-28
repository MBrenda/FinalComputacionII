#include "../include/header.h"

void clean(char * buff){
	int i;
	for(i = 0; i < strlen(buff); i++){
		buff[i] = '\0';
	}
}

char * obtenerFecha() {
	char *fecha = (char *) malloc (128 * sizeof(char));
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);

    strftime(fecha, 128, "%d/%m/%y %H:%M:%S", tlocal);
    
	return fecha;
}

void registrar(char buf[], char ip[]) {

	FILE *log;
	log = fopen("db/log.txt", "a+");

	if (log == NULL) { error("fopen");}
	
	fputs(ip, log);
	fputs(" | ", log);
	fputs(obtenerFecha(), log);
	fputs(" | ", log);
	fputs(strtok(buf, "|"), log);
	fputs("\n", log);
	
	fclose (log);
}

char * enviarTickets() { //nos ubicamos en el espacio fisico donde estan los datos, para enviarlos al cliente y este los vea.

	char caracteres[100];
	char * tickets = (char *) malloc (BUF_SIZE * sizeof(char)); //tickets tiene una direaccion de memoria a la cual se le esta reservando un tamaño.

	clean(tickets);
	clean(caracteres);

	FILE *db;
	db = fopen("db/tickets.txt", "r");

	if (db == NULL) { error("fopen"); }

	while (feof(db) == 0) 
	{
 		fgets(caracteres, 100, db); 
		sprintf(tickets, "%s-%s", tickets, caracteres);
		clean(caracteres);
 	}

    	fclose(db);

	return tickets;
}


void editarTicket(char ticket[] ,char ip[]){ 
	key_t key;
	struct sembuf operacion;
	int sem_id;
	char newID[3],oldID[3], aux[100];	
	char temporal[100];
	
	if((key = ftok("db/tickets.txt", 1)) < 0){
		error("ftok");
		exit(1);
	}

	if ((sem_id = semget(key, 1, IPC_CREAT | 0777)) < 0) {
		error("semget");
		exit(1);
	}

	operacion.sem_num = 0;
	operacion.sem_op =-1;
	operacion.sem_flg = 0;

	if (semop(sem_id, &operacion, 1) == -1) {
		error("semop");
		exit(1);
    	}

	strcpy(aux, ticket);
	strtok(aux, "|");
	
	strcpy(newID,strtok(NULL, "|"));
	while(strtok(NULL,"|") != NULL){
		
	}
	
	FILE *fd2;
	if((fd2=fopen("db/tmp.txt", "w+"))<0){
		printf ("Error al crear el archivo2 para escribir");
		exit(1);		
	}
	
	FILE *fd;
	if((fd=fopen("db/tickets.txt", "r+"))<0){
		printf ("Error al abrir el archivo para escribir");
		exit(1);		
	}
	
	while (feof(fd) == 0){	
		fgets(temporal, 100, fd);
		strcpy(aux,temporal);

		if(strcmp(temporal, "\0")==0){
			goto cerrar ;
		}

		strtok(temporal, "|");
		strcpy(oldID, strtok(NULL, "|"));

		if((strcmp(oldID,newID)) != 0){
			fputs(aux, fd2);
		}else if((strcmp(oldID,newID)) == 0){
			sprintf(temporal, "%s%s", ip, ticket+1);
			fputs(temporal, fd2);
			fputs("\n", fd2);			
		} 
		clean(temporal);	
	}
	
	cerrar:
	//recorre desde el comienzo el archivo
	rewind(fd);
	rewind(fd2);

	fd= fopen("db/tickets.txt", "w+");
	if(fd==NULL){
		printf("Error abrir fd");
	}

	while(feof(fd2) == 0){
		fgets(temporal, 100, fd2);
		if((strcmp(temporal,"")) != 0){
			fputs(temporal, fd);
			clean(temporal);	
		}
	}	

	fclose(fd);
	fclose(fd2);

	if(remove("db/tmp.txt") != 0){
		printf ("Error remove tmp");
	}

	operacion.sem_num = 0;
	operacion.sem_op = 1;
	operacion.sem_flg = 0;
}


void guardarTicket(char buf[], char ip[]){

	int count = 0;
	char caracteres[100];

	FILE *db;

	db = fopen("db/tickets.txt", "a+");
	if (db==NULL) {error("fopen"); exit (1);}

	while(feof(db) == 0){
		fgets(caracteres, 100, db);
		count++;
	}

	sprintf(caracteres, "%d|", count);
	fputs(ip, db);
	fputs("|", db);
	fputs(caracteres, db);
	fputs(obtenerFecha(), db);
	fputs("|", db);
	fputs(buf+2, db);
	fputs("\n", db);

	fclose (db);
	
}

void error(char error[]){
	fprintf(stderr,"%d %s %s\n",errno,error,strerror(errno));
	exit(1);
}
