#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
/* portul folosit */
#define PORT 2014

/* codul de eroare returnat de anumite apeluri */
extern int errno;

void  SIGQUIT_handler(int sig)
{
     exit(1);
}

int main ()
{
  struct sockaddr_in server;	// structura folosita de server
  struct sockaddr_in from;	
  char msg[100];		//mesajul primit de la client 
  char msgrasp[100]=" ";        //mesaj de raspuns pentru client
  int sd;			//descriptorul de socket 

  /* crearea unui socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }

  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));
  
  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;	
  /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
  /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
  
  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 5) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }

  /* servim in mod iterativ clientii... */
  while (1)
    {
      int client[10],nrClienti;
      int length = sizeof (from);
	printf("Introdu marimea camerei\n");
	scanf("%d",&nrClienti);
      printf ("[server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);
	int i=0;
	for(i=0;i<nrClienti;i++)
      client[i] = accept (sd, (struct sockaddr *) &from, &length);


int continua=1,nrC=nrClienti;
for(i=0;i<nrClienti;i++)
{
if(!fork())
{
nrC=i;
break;
}}

if(nrC!=nrClienti)
{
while(continua)
{
      bzero (msg, 100);
      fflush (stdout);
      
      /* citirea mesajului */
      if (read (client[nrC], msg, 100) <= 0)
	{
	  exit(0);		
	}
if(strstr(msg,"quit")!=NULL)
{
printf("Camera de %d clienti inchisa\n",nrClienti);
continua=0;
}
for(i=0;i<nrClienti;i++)
     if (write (client[i], msg, 100) <= 0)
	{
	  exit(0);
	}

}
exit(0);
}
for(i=0;i<nrClienti;i++)
close(client[i]);
 }				/* while */
}				/* main */


