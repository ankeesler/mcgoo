# Makefile for mcgoo

all: lib hey include

PROJECT_NAME=mcgoo
LIBRARY_NAME=lib$(PROJECT_NAME)
LIBRARY_LOCATION=/usr/lib
LIBRARY_FILE=$(LIBRARY_LOCATION)/$(LIBRARY_NAME).so

BUILD_DIR=build
BUILD_DIR_CREATED=$(BUILD_DIR)/created
OBJ_FILES=$(BUILD_DIR)/unit-test.o

CC=gcc
CFLAGS=-Wall -Werror -fpic

$(BUILD_DIR_CREATED):
	mkdir -p $(BUILD_DIR); touch $(BUILD_DIR_CREATED)

$(BUILD_DIR)/unit-test.o: unit-test.c $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBRARY_FILE): $(OBJ_FILES)
	sudo $(CC) $(CFLAGS) -shared -o $@ $(OBJ_FILES)

lib: $(LIBRARY_FILE)

include:
	sudo cp unit-test.h /usr/include/

dynamic: $(LIBRARY_FILE) include

clean:
	rm -rdf $(BUILD_DIR) *.dSYM mcgoo

# MCGOO STUFF

CXX=clang++
CXXFLAGS=-g -Wall -Werror

MCGOO_FILES=mcgoo.cpp
MCGOO_OBJ=$(MCGOO_FILES:.c=.o)
MCGOO_MOD=Mcgoo.pm
MCGOO_LIB=/opt/local/lib/perl5/5.16.3/$(MCGOO_MOD)

ARGS=

hey: $(MCGOO_LIB)

$(MCGOO_LIB): $(MCGOO_MOD)
	sudo cp $< $@

run: mcgoo
	./mcgoo $(ARGS)

mcgoo: $(MCGOO_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^