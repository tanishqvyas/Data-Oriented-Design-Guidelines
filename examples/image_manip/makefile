CC = g++
DEBUG_VAL=0
CPPFLAGS = -DDEBUG=${DEBUG_VAL} -Wall -Werror -std=c++2a -pedantic -Weffc++ -g

all: main.out

main.out: main.o animations.o image.o 
	${CC} $^ ${CPPFLAGS} -o main.out

main.o: main.cpp data.hpp
	${CC} main.cpp ${CPPFLAGS} -c

animations.o: animations.cpp animations.hpp
	${CC} animations.cpp ${CPPFLAGS} -c

image.o: image.cpp image.hpp
	${CC} image.cpp ${CPPFLAGS} -c

.PHONY: clean

clean:
	rm -v *.out
