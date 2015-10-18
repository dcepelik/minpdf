.PHONY: clean

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-Wall
PROG=pd
OBJS=main.o pdf/document.o pdf/page.o

${PROG}: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} $^

%.o: %.cpp
	${CC} ${CFLAGS} -o $@ $<

pdf/%.o: pdf/%.cpp
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -rf -- ${PROG} *.o pdf/*.o
