# $Id: Makefile,v 1.6 2014-02-13 18:58:45-08 - - $

MKFILE    = Makefile
NOINCLUDE = ci clean spotless

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = l8stat.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = l8stat
SOURCES   = ${CSOURCE} ${MKFILE}
LISTSRC   = ${SOURCES}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<
