CC = g++
DEBUG_VAL=0
CPPFLAGS = -DDEBUG=${DEBUG_VAL} -Wall

all: p1.out p2.out

p1.out: MemberBool.cpp
	${CC} $^ ${CPPFLAGS} -o p1.out

p2.out: BoolNotMember.cpp
	${CC} $^ ${CPPFLAGS} -o p2.out

.PHONY: clean

clean:
	rm -v *.out
