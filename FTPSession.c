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
  int recv_len; // Number of bits we receive from the client
  char command[1024]; // Buffer to hold the command sent by client
  
  // Send the 220 greeting message to the client
  send_message(cli_sock,"220-Welcome to the server\n220-Proudly running jk-ftpsv\n220-\n220 Features: a .\n");
  // Note: In multithreaded implementation, may be necessary to implement 421 (temporary rejection) greeting

  // Listen for commands using the TELNET socket
  command_result = 0; // command_result will be 0 unless QUIT is detected
  recv_len = 1; // initialize recv_len
  while(command_result == 0 && recv_len > 0)
  {
    recv_len = printf("in the loop...");
    
    // Receive a command from the client
    recv_len = recv(cli_sock, &command, 1024, 0);
    
    // Parse and act on the command with dispatch_command
    command_result = dispatch_command(command);        
  }

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

