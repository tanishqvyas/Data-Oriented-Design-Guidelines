CC = g++
DEBUG_VAL=0
CPPFLAGS = -DDEBUG=${DEBUG_VAL} -Wall -Werror -std=c++2a -pedantic -Weffc++ -g

all: a.out

a.out: p1.cpp
	${CC} $^ ${CPPFLAGS} 

.PHONY: clean

clean:
	rm -v *.out
