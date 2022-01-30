CC = gcc
CFLAGS=-g -Wall -pedantic

BIN=uniontest

all : $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.dSYM $(BIN)