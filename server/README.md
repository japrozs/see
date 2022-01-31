# pserve

A small and fast multithreaded server written in 100 lines of pure C.
## How it works

```
-> listen for connections
-> receive a connection
-> create a new thread
-> delegate handling the request to that new thread
-> done!
```

## Usage

```bash
make
./server

# create 6 files (1.c, 2.c, 3.c, 4.c, 5.c, 6.c in the /tmp/testfiles directory)
# in a new window
ruby client.rb
```
