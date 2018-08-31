objects = stack.o token_list.o token.o rpn.o
CC=gcc
RM=rm

.c.o:
	$(CC) -O0 -ggdb -c -o $@ $<

all: $(objects)
	$(CC) -O0 -ggdb -o rpn $(objects)

clean:
	rm -f $(objects) rpn.exe *~
