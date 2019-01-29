CFLAGS= -pedantic -Wall -Wextra -Werror -ggdb
default:
	gcc cpu.c -o cpu $(CFLAGS)
