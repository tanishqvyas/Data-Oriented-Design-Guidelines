CC = g++
DEBUG_VAL=0
CPPFLAGS = -DDEBUG=${DEBUG_VAL} -Wall -Werror -std=c++2a -pedantic -Weffc++ -g

all: p1.out p2.out

p1.out: p1.cpp
	${CC} $^ ${CPPFLAGS} -o p1.out

p2.out: p2.cpp
	${CC} $^ ${CPPFLAGS} -o p2.out

.PHONY: clean

clean:
	rm -v *.out
