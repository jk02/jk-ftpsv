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

  send(cli_sock, "220-Welcome to the server\n220-Proudly running jk-ftpsv\n220-\n220 Features: a .", 82, 0);

  // memset(&buffer, 0, sizeof(buffer));

  // recv_len = recv(cli_sock, &buffer, 1024, 0);

  /*  while(recv_len > 0) //Rewrite to be compliant with the RFC
    {
      if(strncmp(buffer, "close", 5) == 0)
	break;
      printf("RECV: %d bytes\n", recv_len);
      printf("%s", &buffer);
      memset(&buffer, 0, sizeof(buffer));
      recv_len = recv(xferSocket, &buffer, 1024, 0);
    }
  */
  
  close(cli_sock);

  return 0;
}

int dispatch_command(char *cid)
{
  
}
