CC=gcc
CFLAGS=-g -Wall -pedantic
BIN=downloadex

all: clean $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lcurl

clean:
	$(RM) -rf $(BIN) *.dSYM