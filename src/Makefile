.PHONY: clean

CC=g++
CFLAGS=-c -std=c++17 -Wall -Wextra --pedantic -g
LDFLAGS=-Wall -Wextra --pedantic
PROG=qutepdf
OBJS=qutepdf.o Element.o Container.o Document.o TextNode.o Paragraph.o\
	Parser.o Box.o Char.o Penalty.o HorizontalGlue.o PDF/Document.o\
	PDF/Page.o PDF/Objects/Object.o PDF/Objects/Array.o\
	PDF/Objects/Dictionary.o PDF/Objects/Literal.o PDF/Objects/Reference.o\
	PDF/Objects/IndirectObject.o

${PROG}: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} $^

%.o: %.cpp %.hpp
	${CC} ${CFLAGS} -o $@ $<

PDF/%.o: PDF/%.cpp PDF/%.hpp
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -rf -- ${PROG} ${OBJS}
