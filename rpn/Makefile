objects = stack.o token.o rpn.o
CC=gcc
RM=rm

.c.o:
	$(CC) -c -o $@ $<

all: $(objects)
	$(CC) -o rpn $(objects)

clean:
	rm $(objects) rpn.exe *~
