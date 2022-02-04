CC=gcc
CPP=g++
CFLAGS=-Wall -g -pedantic
EXE=example1 example2
LFLAGS=-ldl

all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)

%: %.cpp
	$(CPP) $(CFLAGS) -DDEBUG $< -o $@-debug $(LFLAGS)
	$(CPP) $(CFLAGS) $< -o $@-release $(LFLAGS)

clean:
	$(RM) -r *.dSYM *.o $(EXE)