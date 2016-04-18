.PHONY: clean

CC=g++
CFLAGS=-c -std=c++17 -Wall -Wextra --pedantic -g -I$(CURDIR)
LDFLAGS=-Wall -Wextra --pedantic
PROG=qutepdf
OBJS=qutepdf.o\
	BoxModel/Box.o\
	BoxModel/Char.o\
	BoxModel/HList.o\
	BoxModel/HorizontalGlue.o\
	BoxModel/LineBreak.o\
	BoxModel/Penalty.o\
	DocumentModel/Document.o\
	DocumentModel/Elements/Container.o\
	DocumentModel/Elements/Element.o\
	DocumentModel/Elements/Paragraph.o\
	DocumentModel/Elements/TextNode.o\
	Input/ParseError.o\
	Input/Parser.o\
	PDF/Document.o\
	PDF/Objects/Array.o\
	PDF/Objects/Dictionary.o\
	PDF/Objects/Literal.o\
	PDF/Objects/Name.o\
	PDF/Objects/Number.o\
	PDF/Objects/Object.o\
	PDF/Objects/Reference.o\
	PDF/Objects/Stream.o\
	PDF/Page.o\
	PDF/Writer.o\
	Renderer.o

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $^

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf -- $(PROG) $(OBJS)
