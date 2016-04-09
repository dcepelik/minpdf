.PHONY: clean

CC=g++
CFLAGS=-c -std=c++11 -Wall -Wextra --pedantic -g
LDFLAGS=-Wall -Wextra --pedantic
PROG=qutepdf
OBJS=qutepdf.o Element.o Container.o Document.o TextNode.o Paragraph.o\
	Parser.o

${PROG}: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} $^

%.o: %.cpp %.hpp
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -rf -- ${PROG} *.o
