#include        <sys/types.h>   /* basic system data types */

#include        <sys/socket.h>  /* basic socket definitions */

#include 		<unistd.h>

#if TIME_WITH_SYS_TIME
#include        <sys/time.h>    /* timeval{} for select() */

#include        <time.h>                /* timespec{} for pselect() */

#else
#if HAVE_SYS_TIME_H
#include        <sys/time.h>    /* includes <time.h> unsafely */

#else
	#include        <time.h>                /* old system? */

#endif
#endif
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */

#include        <arpa/inet.h>   /* inet(3) functions */

#include        <errno.h>

#include        <fcntl.h>               /* for nonblocking */

#include        <netdb.h>

#include        <signal.h>

#include        <stdio.h>

#include        <stdlib.h>

#include        <string.h>

#include		<unistd.h>

#include        "stdio.h"

#include        "string.h"

#include 		"database.h"

#define MAXLINE 1024

//#define SA struct sockaddr

#define LISTENQ 2

char * remove_spaces(char * str) {
    int i = 0, j, chk;
    while (str[i] != '\0') {
        chk = 0;
        if (str[i] == ' ' || str[i] == '\n') {
            j = i;
            while (str[j - 1] != '\0') {
                str[j] = str[j + 1];
                j++;
            }
            chk = 1;
        }
        if (chk == 0)
            i++;
    }
    return str;
}
int main(int argc, char ** argv) {
    int listenfd, connfd, n, pid;
    socklen_t len;
    char recvline[MAXLINE + 1], recvline2[MAXLINE + 1],str[INET6_ADDRSTRLEN + 1];
    char subscribed[MAXLINE + 1];
    time_t ticks;
    struct sockaddr_in servaddr, cliaddr;
    //char a[100];
	clear_table();
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket error : %s\n", strerror(errno));
        return 1;
    }

    int val = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, & val, sizeof(val)) < 0) {
        fprintf(stderr, "SO_REUSEADDR setsockopt error : %s\n", strerror(errno));
    }

    //sleep(3);
    bzero( & servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1234); /* daytime server */

    if (bind(listenfd, (struct sockaddr * ) & servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "bind error : %s\n", strerror(errno));
        return 1;
    }
    //sleep(3);
    if (listen(listenfd, LISTENQ) < 0) {
        fprintf(stderr, "listen error : %s\n", strerror(errno));
        return 1;
    }
    //sleep(3);

    signal(SIGCHLD, SIG_IGN);

    for (;;) {
        

        printf("Waiting for connection \n");
		
        len = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr * ) & cliaddr, & len)) < 0) {
            fprintf(stderr, "accept error : %s\n", strerror(errno));
            continue;
        }

        if ((pid = fork()) == 0) {
            close(listenfd);
			fcntl(connfd, F_SETFL,  O_NONBLOCK);	//zmiana flag deskryptora
            bzero(str, sizeof(str));
			bzero(recvline, sizeof(recvline));
            inet_ntop(AF_INET, (struct sockaddr * ) & cliaddr.sin_addr, str, sizeof(str));
			int x;
			
            printf("Connection from %s\n", str);
			
			while(1){
				//printf("while begin in: %s\n", str);
				if ((n = read(connfd, recvline, MAXLINE)) > 0) {	//jeśli read zwraca 0 gdy nie ma nic do odczytania
					printf("n=%d\n\r", n);
					recvline[n] = 0; /* null terminate */


					int a = atoi(recvline);
					char recvline_chopped[MAXLINE+1];
					printf("a=%d\n\r", a);
					switch (a) {
					case 1:{
						bzero(recvline, sizeof(recvline));
						while(read(connfd, recvline, MAXLINE)<1){sleep(1);}	//czekanie aż coś sie pojawi w deskryptorze

						strcpy(recvline_chopped , remove_spaces(recvline));
						add_topic(str, recvline_chopped);	//nie trezba sprawdzac czy juz jest wpisany
						print_table();
					break;}
					case 2:{
						bzero(recvline, sizeof(recvline));
						while(read(connfd, recvline, MAXLINE)<1){sleep(1);}
						strcpy(recvline_chopped , remove_spaces(recvline));
						remove_topic(str, recvline_chopped);
						print_table();
					break;}
					case 4:{
						bzero(recvline, sizeof(recvline));
						printf("making a message\n\r");
						char topic[16];
						bzero(topic, sizeof(topic));
						while(read(connfd, topic, 16)<1){sleep(1);}
						printf("requested a topic: %s\n\r",topic);
						topic[strlen(topic)-1]=0;
						bzero(recvline, sizeof(recvline));
						while(read(connfd, recvline, MAXLINE)<1){sleep(1);}
						printf("\n\rrequested a message: %s\n\r",recvline);

						write_to_send(topic,recvline);	// write_to_send(hashtag,tresc wiadomosci(max 255 charów)
						print_all();
						//x=fcntl(connfd ,F_GETFL, 0);
						//fcntl(connfd, F_SETFL, x | O_NONBLOCK);
					break;}
					case 3:
					{
						printf("client %s is listening...\n\r",str);
						break;
					}
					case 9:{
						print_all();				
	
					break;}
					case 5:{
						close(connfd);
						printf("Client %s disconnected\n", str);
						exit(0);
						
					break;}

					default:{
						printf("\nWrong input!\n");
					break;}
					}
					bzero(recvline, sizeof(recvline));

				}
				
				char mess[255];
				if(check_to_send(str,mess)){ //sprawdx czy masz wyslac wiadomosc check_to_send(swoj adres ip ,adres gdzie wiadomosc ma byc zapisana)
					printf("trying to send message to %s\n\r",str);
					if(write(connfd,mess,strlen(mess))<0){
						printf("write error : %s\n", strerror(errno));
					}
					//send
				}
				sleep(1);

			}
            
        } else {
            close(connfd);
        }
    }
}