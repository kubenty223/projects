#include   <sys/types.h>   /* basic system data types */

#include   <sys/socket.h>  /* basic socket definitions */

#include   <netinet/in.h>  /* sockaddr_in{} and other Internet defns */

#include   <arpa/inet.h>   /* inet(3) functions */

#include   <errno.h>

#include   <stdio.h>

#include   <stdlib.h>

#include   <unistd.h>

#include   <string.h>
#include <fcntl.h>

#define MAXLINE 1024
#define SA struct sockaddr

int
main(int argc, char ** argv) {
    int sockfd, n, err;
    struct sockaddr_in servaddr;
    char str[INET_ADDRSTRLEN + 1];
    char buf[MAXLINE];
	char recvline[MAXLINE + 1];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <IPaddress> \n", argv[0]);
        return 1;
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket error : %s\n", strerror(errno));
        return 1;
    }
	
    //sleep(3);
    bzero( & servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1234); /* daytime server */
    if ((err = inet_pton(AF_INET, argv[1], & servaddr.sin_addr)) == -1) {
        fprintf(stderr, "ERROR: inet_pton error for %s : %s \n", argv[1], strerror(errno));
        return 1;
    } else if (err == 0) {
        fprintf(stderr, "ERROR: Invalid address family \n");
        return 1;
    }

    if (connect(sockfd, (SA * ) & servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "connect error : %s \n", strerror(errno));
        return 1;
    }

    printf("Connected \n");
    int warunek = 1;
    while (warunek) {
        printf("What do you want to do ? \n\n1.Subscribe a topic.\n2.Unsubscribe a topic.\n3.Receive information on subscribed topics.\n4.Write information on subscribed topic.\n5.Exit\n");
        printf("Your choice: ");
		//zeruj
		bzero(buf, sizeof(buf));
        fgets(buf, 256, stdin);
        if (write(sockfd, buf, strlen(buf)) < 0) {
            fprintf(stderr, "write error : %s\n", strerror(errno));
        }
		//zeruj
		
        switch (atoi(buf)) {
        case 1: {
			bzero(buf, sizeof(buf));
            printf("What topic you want to subscribe?\n");
            fgets(buf, 256, stdin);
            if (write(sockfd, buf, strlen(buf)) < 0) {
                fprintf(stderr, "write error : %s\n", strerror(errno));
            }
            break;
        }

        case 2: {
			bzero(buf, sizeof(buf));
            printf("What topic you want to unsubscribe?\n");
            fgets(buf, 256, stdin);
            if (write(sockfd, buf, strlen(buf)) < 0) {
                fprintf(stderr, "write error : %s\n", strerror(errno));
            }

            break;
        }
		case 3: {
			bzero(buf, sizeof(buf));
			fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
			fcntl(sockfd, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
			printf("wcisnij enter aby zakonczyc nasluchiwanie\n\r");
			while(1){
				
			if ((fgets(buf, 256,stdin)) > 0) {
				
				break;
			}			
			
			bzero(recvline, sizeof(recvline));

            if(read(sockfd,recvline,MAXLINE)>0){				
				printf("%s\n\n\r",recvline);
			}
			//printf("n=%d\n\r", n);
			}
            break;
        }
		case 4:{
			bzero(buf, sizeof(buf));
			printf("What topic you want to write to?\n");
            fgets(buf, 256, stdin);
            if (write(sockfd, buf, strlen(buf)) < 0) {
				
                fprintf(stderr, "write error : %s\n", strerror(errno));
            }
			bzero(buf, sizeof(buf));
			printf("What message you want to send?\n");
			
            fgets(buf, 256, stdin);
            if (write(sockfd, buf, strlen(buf)) < 0) {
                fprintf(stderr, "write error : %s\n", strerror(errno));
            }
			break;
		}
        case 5: {
			bzero(buf, sizeof(buf));
            warunek = 0;
            break;
        }

        default: {
			bzero(buf, sizeof(buf));
            printf("\nWrong number\n");
            break;
        }
        }
		
		fcntl(0, F_SETFL, fcntl(0, F_GETFL) &(~O_NONBLOCK));
		fcntl(sockfd, F_SETFL, fcntl(0, F_GETFL) &(~O_NONBLOCK));

        //printf("%s",buf);
        fflush(stdout);
    }
    //sleep(10);
    exit(0);
}