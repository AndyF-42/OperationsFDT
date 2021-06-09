CC=gcc
CFLAGS=-g -Wall -lm
DFLAGS=
PROGS=operations

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*
