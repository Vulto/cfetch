#!/bin/bash
VERSION = 1.0
PREFIX = /usr/local/bin/
BIN = cfetch
SOURCE= cfetch.c

CC = clang
CFLAGS = -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wmissing-include-dirs -Wfatal-errors -O3 -o

make: 
	$(CC) $(CFLAGS) $(BIN) $(SOURCE)

install:
	$(CC) $(CFLAGS) $(BIN) $(SOURCE)
	cp -f $(BIN) $(DESTDIR)$(PREFIX)

clean:
	rm $(BIN) 

uninstall:
	rm $(PREFIX)$(BIN) 
