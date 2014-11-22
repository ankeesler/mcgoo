###############################################################################
# Makefile for mcgoo
###############################################################################

all: global

#######################################
# Shared stuff
#######################################

CC=gcc
CFLAGS=-Wall -Werror -g

BUILD_DIR=build
BUILD_DIR_CREATED=$(BUILD_DIR)/created
OBJ_FILES=$(BUILD_DIR)/unit-test.o

RM=rm -rdf
RM_STUFF=$(BUILD_DIR) *.dSYM

$(BUILD_DIR_CREATED):
	mkdir -p $(BUILD_DIR); touch $(BUILD_DIR_CREATED)

clean:
	$(RM) $(RM_STUFF)
	
#######################################
# Global install stuff
#######################################

global: dynamic module

#######################################
# C unit test library stuff
#######################################

LIBRARY_NAME=libmcgoo
LIBRARY_LOCATION=/usr/lib
LIBRARY_FILE=$(LIBRARY_LOCATION)/$(LIBRARY_NAME).so

$(BUILD_DIR)/unit-test.o: unit-test.c $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -fpic -o $@ -c $<

$(LIBRARY_FILE): $(OBJ_FILES)
	sudo $(CC) $(CFLAGS) -fpic -shared -o $@ $(OBJ_FILES)

lib: $(LIBRARY_FILE)

include: unit-test.h
	sudo cp unit-test.h /usr/include/

dynamic: $(LIBRARY_FILE) include

#######################################
# Mcgoo Perl Module thing
#######################################

MCGOO_MOD=Mcgoo.pm
MCGOO_LIB=/System/Library/Perl/Extras/5.18/$(MCGOO_MOD)

$(MCGOO_LIB): $(MCGOO_MOD)
	sudo cp $< $@

module: $(MCGOO_LIB)
