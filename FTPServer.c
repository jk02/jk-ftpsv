// jk-ftpsrv
// Basic FTP Server
// FTPServer.c - Accepts connections [and transfers files]
//
// Author: jk02
//
// This public domain software comes with NO WARRANTY.  See LICENSE in the repository for further details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int make_socket(uint16_t);

int main(int argc, char *argv[])
{
  uint16_t portNum;
  socklen_t cliSize;
  int socket,xferSocket;
  struct sockaddr_in cliAddr;
    
  printf("**********FTP SERVER***********\n");
  printf("Please enter a port: ");
  scanf("%u", &portNum);

  socket = make_socket(portNum);
  printf("%d\n", socket); // Debug message to print socket file descriptor


  // Main program loop
  // Currently supports only one connection at a time
  // TODO: Add multithreading to support simultaneous connections
  while(1)
    {
      // Listen for connections
      listen(socket, 5);
      printf("Awaiting connections...\n");
      cliSize = sizeof(cliAddr);
      // Establish TELNET socket with the client
      if(xferSocket = accept(socket, (struct sockaddr*) &cliAddr, &cliSize) < 0)
	{
	  perror("Fatal: Could not accept connection");
	  exit(EXIT_FAILURE);
	}
      puts("Accepted a client connection.");
      // Start the FTP session per the example from the Java code... 
      exit(EXIT_SUCCESS);
    }
  
}

int make_socket(uint16_t port)
{
  int newSock = -1;
  struct sockaddr_in name;

  // Zero out the address struct, just to be sure
  bzero((char *) &name, sizeof(name));
  
  // Attempt to create a new socket
  newSock = socket(PF_INET, SOCK_STREAM, 0);
  if(newSock < 0)
    {
      perror("Fatal: Could not create network socket");
      exit(EXIT_FAILURE);
    }

  // Provide the socket with an address
  name.sin_family = AF_INET;
  name.sin_port = htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(newSock, (struct sockaddr *) &name, sizeof(name)) < 0)
    {
      perror("Fatal: Could not bind address to socket");
      exit(EXIT_FAILURE);
    }
  
  return newSock;
}
