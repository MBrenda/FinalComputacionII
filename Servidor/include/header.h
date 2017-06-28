#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> //Quita un warning
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //Quita un warning.
#include <dirent.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/mman.h>

#define BUF_SIZE 1024

void clean(char *);

char * enviarTickets();

void editarTicket(char [], char []);

void guardarTicket(char [], char []);

void registrar(char [], char []);

char * obtenerFecha();

void error(char []);


