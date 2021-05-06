CC = g++
DEBUG_VAL=0
CPPFLAGS = -DDEBUG=${DEBUG_VAL} -Wall -Werror -std=c++2a -pedantic -Weffc++ -g

all: main.out

main.out: main.o animations.o
	${CC} $^ ${CPPFLAGS} -o main.out

main.o: main.cpp
	${CC} $^ ${CPPFLAGS} -c

animations.o: animations.cpp
	${CC} $^ ${CPPFLAGS} -c

.PHONY: clean

clean:
	rm -v *.out
