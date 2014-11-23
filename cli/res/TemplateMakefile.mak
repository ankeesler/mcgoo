# Mcgoo test framework makefile.

all: test

CC=clang
CFLAGS=-g -Wall -Werror

COMPILE=$(CC) $(CFLAGS) $@ -c $<

RM=rm
RM_STUFF=

TESTS=

test: $(TESTS)

clean:
	$(RM) $(RM_STUFF)

