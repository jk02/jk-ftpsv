CC=clang
CFLAGS=-g -I.
DEPS=jkftpsv.h
OBJ=FTPServer.c FTPSession.c FTPCommand.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

jk-ftpsv: $(OBJ)
	@echo "Caution: Debug information being generated..."
	$(CC) -o $@ $^ $(CFLAGS)
