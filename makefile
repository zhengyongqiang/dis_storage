.PHONY:clean all

WORKDIR = .
VPATH = ./src

CC = gcc
CFLGS = -Wall -g -I$(WORKDIR)/inc/ -I/usr/local/include/hiredis
LIBFLAG = -L/usr/local/lib/ -lhiredis

BIN = main

all:$(BIN)

main:main.o make_log.o redis_op.o
	$(CC) $(LIBFLAG) $(CFLGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)