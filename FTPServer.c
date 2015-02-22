// jk-ftpsv
// Basic FTP Server
// FTPServer.c - Accepts connections [and transfers files]
//
// Author: jk02
//
// This public domain software comes with NO WARRANTY.  See LICENSE in the repository for further details.

#include "jkftpsv.h"

int main(int argc, const char *argv[])
{
  uint16_t portNum;
  socklen_t cliSize;
  int socket,xferSocket,recv_len;
  char buffer[1024];
  struct sockaddr_in cliAddr;
    
  printf("**********FTP SERVER***********\n");

  if(argc > 1)
    {
      portNum = (uint16_t) strtol(argv[1], NULL, 10);
    } else {
    printf("Please enter a port: ");
    scanf("%hu", &portNum);
  }

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
      xferSocket = accept(socket, (struct sockaddr*) &cliAddr, &cliSize);
      if(xferSocket < 0)
	{
	  perror("Fatal: Could not accept connection");
	  exit(EXIT_FAILURE);
	}

      printf("%d\n", xferSocket); // Debug message to print socket fd
      
      printf("Server: got connection from %s on port %d.\n",
	     inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

      // Start the session here

      invoke_session(xferSocket);
    }
  exit(EXIT_SUCCESS);
}

int make_socket(uint16_t port)
{
  int newSock = -1; //FD of the socket we are creating
  int yes = 1; // Needed for setsockparam
  struct sockaddr_in name;

  // Zero out the address struct
  memset(&name, 0, sizeof(name));
  
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

  // Bind address to the socket
  if(bind(newSock, (struct sockaddr *) &name, sizeof(name)) < 0)
    {
      perror("Fatal: Could not bind address to socket");
      exit(EXIT_FAILURE);
    }

  // Set the SO_REUSEADDR param to ensure the port is reusable
  if(setsockopt(newSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      perror("Fatal: Could not set appropriate socket options.");
      exit(EXIT_FAILURE);
    }
    
  return newSock;
}
