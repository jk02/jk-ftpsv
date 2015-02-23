// jk-ftpsv
// Basic FTP Server
// FTPSession.c - Governs the client-server FTP session
// and transfers files.
//
// Author: jk02
//
// This public domain software comes with NO WARRANTY.  See LICENSE in the repository for further details.

#include "jkftpsv.h"

// Invokes an FTP session with a client
// cli_sock is passed to the function by main (xferSocket)
int invoke_session(int cli_sock)
{
  int ft_socket; // Socket used for file transfer
  int command_result; // Used to monitor session status (breaks if 1)
  char command[1024]; // Buffer to hold the command sent by client
  struct pollfd clifd[1];
  
  // Send the 220 greeting message to the client
  send_message(cli_sock,"220-Welcome to the server\n220-Proudly running jk-ftpsv\n220-\n220 Features: a .\n");
  // Note: In multithreaded implementation, may be necessary to implement 421 (temporary rejection) greeting

  // Setup clifd so it is possible to poll the connection
  memset(&clifd, 0, sizeof(clifd));
  clifd[1].fd = cli_sock;
  clifd.events = POLLIN | POLLOUT;
  
  // Listen for commands using the TELNET socket
  command_result = 0; // command_result will be 0 unless QUIT is detected
  do {
      printf("in the loop...");
      // Poll the socket to make sure the client has not disconnected
      int alive;
      printf("polling connection...");
      alive = poll(&clifd, 1, 3500); // Poll the connection, waiting 3500ms
      if(alive == -1)
	perror("Error polling connection.");
      else if(alive == 0)
	{
	  printf("Client disconnected or timed out.");
	  close(cli_sock);
	  return 0;
	}
      // Receive a command from the client
      recv(cli_sock, &command, 1024, 0);

      // Parse and act on the command with dispatch_command
      command_result = dispatch_command(command);        
  } while(command_result == 0);

  // Close the control connection
  send_message(cli_sock, "221 Bye.\n");
  close(cli_sock);

  return 0;
}

// Dispatcher for the various commands defined in RFC 909
// The commands themselves are handled in FTPCommand.c
int dispatch_command(char *cid)
{
  if(strncmp(cid,"QUIT",4) == 0) {
      return 1;
  }

  return 0;
}

void send_message(int sock, char *message)
{
  int message_length;

  message_length = strlen(message);

  send(sock, message, message_length, 0);
}

