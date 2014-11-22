# makefile for test of unit test, ugh

all: run-perl-test run-simple-perl-test run-test
	;

test: test.o
	cc -o test -lmcgoo -Wall -Werror test.o

run-test: test
	./test

run-perl-test:
	./perl-test.pl

run-simple-perl-test:
	./simple-perl-test.pl

clean:
	rm -f test.o test