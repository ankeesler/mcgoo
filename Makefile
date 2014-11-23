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

STAGE_DIR=stage

.PHONY: stage
stage: cp-res
	
clean-stage:
	rm -fdr $(STAGE_DIR)/*.mak
	
test-all: global cli-test perl-test lib-test
	
#######################################
# Global install stuff
#######################################

global: dynamic module cli-global

#######################################
# C unit test library stuff
#######################################

LIBRARY_NAME=libmcgoo
LIBRARY_LOCATION=/usr/lib
LIBRARY_FILE=$(LIBRARY_LOCATION)/$(LIBRARY_NAME).so

LIBRARY_TEST_FILE=test.c
LIBRARY_TEST_OBJ=$(shell echo $(LIBRARY_TEST_FILE) | sed -E -e 's/([a-z\-]+).c/$(BUILD_DIR)\/\1.o/g')
LIBRARY_TEST_EXE=$(BUILD_DIR)/test

$(LIBRARY_TEST_EXE): test/test.c $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -lmcgoo -o $@ $<

$(BUILD_DIR)/unit-test.o: unit-test.c $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -fpic -o $@ -c $<

$(LIBRARY_FILE): $(OBJ_FILES)
	sudo $(CC) $(CFLAGS) -fpic -shared -o $@ $(OBJ_FILES)

lib: $(LIBRARY_FILE)

include: unit-test.h
	sudo cp unit-test.h /usr/include/

dynamic: $(LIBRARY_FILE) include

lib-test: $(LIBRARY_TEST_EXE) dynamic
	$<

#######################################
# Mcgoo Perl Module thing
#######################################

MCGOO_MOD=Mcgoo.pm
MCGOO_LIB=/System/Library/Perl/Extras/5.18/$(MCGOO_MOD)

MCGOO_PERL_TEST=test/perl-test.pl
MCGOO_PERL_SIMPLE_TEST=test/simple-perl-test.pl

$(MCGOO_LIB): $(MCGOO_MOD)
	sudo cp $< $@

module: $(MCGOO_LIB)

perl-regular-test:
	$(MCGOO_PERL_TEST)
perl-simple-test:
	$(MCGOO_PERL_SIMPLE_TEST)
perl-test: perl-regular-test perl-simple-test

#######################################
# Cli stuff
#######################################

MCGOO_CLI_EXE_NAME=mcgoo
MCGOO_CLI_EXE_DIR=/usr/bin
MCGOO_CLI_EXE=$(MCGOO_CLI_EXE_DIR)/$(MCGOO_CLI_EXE_NAME)

MCGOO_CLI_SRC=main.c makefile.c
MCGOO_CLI_OBJ=$(shell echo $(MCGOO_CLI_SRC) | sed -E -e 's/([a-z\-]+).c/$(BUILD_DIR)\/\1.o/g')

ARGS=

MCGOO_CLI_TEST_SCRIPT_DIR=cli/test/
MCGOO_CLI_TEST_SCRIPT_NAME=mcgoo-test.pl
MCGOO_CLI_TEST_SCRIPT=$(MCGOO_CLI_TEST_SCRIPT_DIR)/$(MCGOO_CLI_TEST_SCRIPT_NAME)

RES_DIR=cli/res

$(BUILD_DIR)/main.o: cli/main.c $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/makefile.o: cli/makefile.c $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/$(MCGOO_CLI_EXE_NAME): $(MCGOO_CLI_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

cli: $(BUILD_DIR)/$(MCGOO_CLI_EXE_NAME)

run-cli: cli
	$(BUILD_DIR)/$(MCGOO_CLI_EXE_NAME) $(ARGS)

$(MCGOO_CLI_EXE_DIR)/$(MCGOO_CLI_EXE_NAME): $(MCGOO_CLI_OBJ)
	sudo $(CC) $(CFLAGS) -o $@ $^

cli-global: $(MCGOO_CLI_EXE_DIR)/$(MCGOO_CLI_EXE_NAME)

cp-res:
		cp -R $(RES_DIR) $(STAGE_DIR)

cli-test: cli-global stage
	cd $(STAGE_DIR); ../$(MCGOO_CLI_TEST_SCRIPT); cd ..