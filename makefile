CFLAGS= -pedantic -Wall -Wextra -Werror
default:
	gcc cpu.c -o cpu $(CFLAGS)
