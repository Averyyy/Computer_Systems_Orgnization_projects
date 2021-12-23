# Makefile for project 1
#
# You should not need to modify this file.

CC		= gcc

CFLAGS		= -g  -Wall

all: p4 run_p4

p4: p4.c
	$(CC) $(CFLAGS) -o p4 p4.c

run_p4: p4
	./p4
clean:
	rm -f *~ *.o a.out core p4