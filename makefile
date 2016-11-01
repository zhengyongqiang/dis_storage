.PHONY:clean all

WORKDIR = .
VPATH = ./src

CC = gcc
CFLGS = -Wall -g -I$(WORKDIR)/inc/
LIBFLAG = -L

BIN = main

all:$(BIN)

main:main.o make_log.o
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
