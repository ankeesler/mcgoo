# Makefile for mcgoo cli

all: run

MCGOO_FILES=mcgoo.c makefile.c
MCGOO_OBJ=$(shell echo $(MCGOO_FILES) | sed -E -e 's/([A-Za-z\-]+).c/$(BUILD_DIR)\/\1.o/g')

ARGS=

BUILD_DIR=build
BUILD_DIR_CREATED=$(BUILD_DIR)/created

$(BUILD_DIR_CREATED):
	mkdir -p $(BUILD_DIR); touch $(BUILD_DIR_CREATED)

$(BUILD_DIR)/mcgoo.o: mcgoo.c $(BUILD_DIR_CREATED)
	cc -g -Wall -Werror -o $@ -c $<

$(BUILD_DIR)/makefile.o: makefile.c makefile.h $(BUILD_DIR_CREATED)
	cc -g -Wall -Werror -o $@ -c $<

$(BUILD_DIR)/mcgoo: $(MCGOO_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

compile: $(BUILD_DIR)/mcgoo

run: $(BUILD_DIR)/mcgoo
	./$< $(ARGS)

clean:
	rm -rdf $(BUILD_DIR) Mcgoo.mak

.PHONY: test
test: 
	./test/mcgoo-test.pl