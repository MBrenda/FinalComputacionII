#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //Quita un warning
 
#define BUF_SIZE 1024

void error(char []);

void clean(char *);

char * ingresarTicket(int, char []);

void listarTickets(char []);
