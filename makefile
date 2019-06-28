.PHONY: clean
CC = gcc
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = include

_OBJ = cpu.o status.o main.o instructions.o opcode.o mneumonics.o
OBJ = $(addprefix $(OBJ_DIR)/, $(_OBJ)) 

TARGET = cpu
CFLAGS = -pedantic -Wall -Wextra -Werror -ggdb -I$(INC_DIR) -fsanitize=address -lasan

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS) 

clean: 
	rm $(OBJ) $(TARGET)
