// jk-ftpsv
// Basic FTP Server
// FTPCommand.c - Handles FTP commands as defined in RFC 959
// and transfers files.
//
// Author: jk02
//
// This public domain software comes with NO WARRANTY.  See LICENSE in the repository for further details.

#include "jkftpsv.h"

void cmd_noop(client_session* sesh)
{
  send_message(sesh->control_sock, "200 OK.\n");
}
