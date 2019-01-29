OBJECTS = cpu.o status.o
CFLAGS= -pedantic -Wall -Wextra -Werror -ggdb

default: $(OBJECTS)
	gcc $(OBJECTS) -o cpu $(CFLAGS)
