/* A simple server/client in the internet domain using TCP
   The port number is passed as an argument
https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/client.c
https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/server.c
https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, wroteit;

    struct sockaddr_in serv_addr;
    struct hostent *server;

/* This part of the code ensures that there is a port number argv[2] and
 * IP address/hostname argv[1] entered on the command line
*/
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);

/* a client also needs to set up their side of the socket
 * this uses the "sockfd" call initiates the socket and opens the
 * ephemeral port used temporarily for the server to send responses
 * sockfd here is using the ephemeral port and the client IP adddress
 * gethostbyname resolves hostnames to IP addresses but does nothing
 * if an IP address is given
 * the "connect" command uses the information from the command line to 
 * access the server and port we intend to connect to
*/ 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

/* if the client has made it here "connect" has done its job by using 
 * its side of the socket to connect tot he servers side of the socket
 * and can begin sending a message and receiving a response
*/ 
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    wroteit = write(sockfd,buffer,strlen(buffer));
    if (wroteit < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    wroteit = read(sockfd,buffer,255);
    if (wroteit < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}
