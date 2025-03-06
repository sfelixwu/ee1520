# Makefile for NCKU ee1520 Spring 2025
# instructor, Shyhtsun Felix Wu (sfelixwu@gs.ncku.edu.tw)
#

CC = gcc

# the followings might need to be modified for different platforms

CFLAGS = -g

# CFLAGS = -g -I/usr/include/jsoncpp
# CFLAGS = -g -D_EE1520_DEBUG_ -I/usr/include/jsoncpp
# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# rules to build

all: 	stack_executable

#

stack_main.o:		stack_main.c stack_01.h
	$(CC) -c $(CFLAGS) stack_main.c

stack_foo.o:		stack_foo.c stack_01.h
	$(CC) -c $(CFLAGS) stack_foo.c

stack_bar.o:		stack_bar.c stack_01.h
	$(CC) -c $(CFLAGS) stack_bar.c

stack_baz.o:		stack_baz.c stack_01.h
	$(CC) -c $(CFLAGS) stack_baz.c

stack_address.o:	stack_address.c stack_01.h
	$(CC) -c $(CFLAGS) stack_address.c

stack_executable:	stack_main.o stack_foo.o stack_bar.o stack_baz.o stack_address.o
	$(CC) stack_main.o stack_foo.o stack_bar.o stack_baz.o stack_address.o -o stack_executable

clean:
	rm -f	*.o *~ core stack_executable

