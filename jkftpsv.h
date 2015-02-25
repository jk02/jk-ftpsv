// jk-ftpsv
// Basic FTP Server
// ftpsv.h - Project header file
//
// Author: jk02
//
// This public domain software comes with NO WARRANTY.  See LICENSE in the repository for further details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#ifndef FTPSV_H
#define FTPSV_H

typedef struct client_session { // struct storing key information on this session
  int control_sock; // the TELNET socket (= cli_sock)
  int ft_sock; // the file transfer socket (not yet opened)
  char* uid; // username set by the USER command
} client_session;

int make_socket(uint16_t);
int invoke_session(int);
int dispatch_command(char*,client_session*);
void send_message(int,char*);

// Begin command handling function prototypes
void cmd_noop(client_session*);

#endif /* FTPSV_H */

