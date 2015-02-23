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

int make_socket(uint16_t);
int invoke_session(int);
int dispatch_command(char*);
void send_message(int,char*);

#endif /* FTPSV_H */

