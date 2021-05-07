CC = g++
DEBUG_VAL=0
CPPFLAGS = -DDEBUG=${DEBUG_VAL} -Wall -Werror -std=c++2a -pedantic -O3 -Weffc++ -g

all: main.out

main.out: main.o filters.o image.o
	${CC} $^ ${CPPFLAGS} -o main.out

main.o: main.cpp image.hpp filters.hpp
	${CC} main.cpp ${CPPFLAGS} -c

filters.o: filters.cpp filters.hpp pixel_data.hpp
	${CC} filters.cpp ${CPPFLAGS} -c

image.o: image.cpp image.hpp pixel_data.hpp
	${CC} image.cpp ${CPPFLAGS} -c

.PHONY: clean

clean:
	rm -v *.out
