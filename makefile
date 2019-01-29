CC = gcc
OBJECTS = cpu.o status.o
TARGET = cpu
CFLAGS = -pedantic -Wall -Wextra -Werror -ggdb

default: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

clean: 
	rm $(OBJECTS) $(TARGET)
