###############################################################################
# Makefile for mcgoo
###############################################################################

all: global

#######################################
# Shared stuff
#######################################

CC=gcc
CFLAGS=-Wall -Werror -g -O0

BUILD_DIR=build
BUILD_DIR_CREATED=$(BUILD_DIR)/created

RM=rm -rdf
RM_STUFF=$(BUILD_DIR) *.dSYM

$(BUILD_DIR_CREATED):
	mkdir -p $(BUILD_DIR); touch $(BUILD_DIR_CREATED)

clean:
	$(RM) $(RM_STUFF)

STAGE_DIR=stage

test-all: global run-java-test perl-test lib-test

#######################################
# Global install stuff
#######################################

global: dynamic module java-lib

#######################################
# C unit test library stuff
#######################################

LIBRARY_NAME=libmcgoo
LIBRARY_LOCATION=/usr/lib
LIBRARY_FILE=$(LIBRARY_LOCATION)/$(LIBRARY_NAME).so

UNIT_TEST_HEADER=c/unit-test.h

$(BUILD_DIR)/%.o: c/test/%.c $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: c/%.c c/%.h $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -fpic -o $@ -c $<

$(BUILD_DIR)/unit-test-unit-test.o: c/unit-test.c $(UNIT_TEST_HEADER) $(BUILD_DIR_CREATED)
	$(CC) $(CFLAGS) -fpic -DUNIT_TEST_UNIT_TEST -o $@ -c $<

$(LIBRARY_FILE): $(BUILD_DIR)/unit-test.o | $(UNIT_TEST_HEADER)
	sudo $(CC) $(CFLAGS) -fpic -shared -o $@ $^

lib: $(LIBRARY_FILE)

include: $(UNIT_TEST_HEADER)
	sudo cp $^ /usr/include/

dynamic: $(LIBRARY_FILE) include

$(BUILD_DIR)/lib-test: $(BUILD_DIR)/unit-test-unit-test.o $(BUILD_DIR)/test.o
	$(CC) $(CFLAGS) -o $@ $^

lib-test: $(BUILD_DIR)/lib-test dynamic
	$<

#######################################
# Mcgoo Perl Module thing
#######################################

MCGOO_MOD_NAME=Mcgoo.pm
MCGOO_MOD=perl/$(MCGOO_MOD_NAME)
PERL_VERSION=5.16
MCGOO_LIB=/System/Library/Perl/Extras/$(PERL_VERSION)/$(MCGOO_MOD_NAME)

MCGOO_PERL_TEST=perl/test/perl-test.pl
MCGOO_PERL_SIMPLE_TEST=perl/test/simple-perl-test.pl

$(MCGOO_LIB): $(MCGOO_MOD)
	sudo cp $< $@

module: $(MCGOO_LIB)

perl-regular-test:
	$(MCGOO_PERL_TEST)
perl-simple-test:
	$(MCGOO_PERL_SIMPLE_TEST)
perl-test: perl-regular-test perl-simple-test

#######################################
# Java stuff
#######################################

JAVA_STUFF_DIR=java

JAVA_SRC_DIR=$(JAVA_STUFF_DIR)/mcgoo
JAVA_TST_DIR=$(JAVA_STUFF_DIR)/test

JAR_NAME=mcgoo.jar
JAR_LOCATION=/usr/local/lib
MCGOO_JAR=$(JAR_LOCATION)/$(JAR_NAME)

java-lib: $(MCGOO_JAR)

mcgoo-package: $(JAVA_SRC_DIR)/*.java | $(BUILD_DIR_CREATED)
	javac $^ -d $(BUILD_DIR) 

java-test: java-lib
	javac -cp $(MCGOO_JAR) $(JAVA_TST_DIR)/*.java -d $(BUILD_DIR)

run-java-test: java-test
	cd $(BUILD_DIR); java test.Test

$(MCGOO_JAR): mcgoo-package
	cd $(BUILD_DIR); sudo jar cf $@ mcgoo/*.class
