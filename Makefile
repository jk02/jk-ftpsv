CC=clang
CFLAGS=-I.

jk-ftpsv: FTPServer.c FTPSession.c
	$(CC) -o jk-ftpsv FTPServer.c FTPSession.c
