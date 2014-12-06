//
// makefile.h
// Andrew Keesler
// November 22, 2014
//
// A makefile.

#ifndef __MAKEFILE_H__
#define __MAKEFILE_H__

#define MAKEFILE_DEFAULT_NAME "Mcgoo.mak"

// Errors.
#define MAKEFILE_SUCCESS 0
#define MAKEFILE_ALREADY_CREATED 1
#define MAKEFILE_NOT_CREATED 2
#define MAKEFILE_CANNOT_OPEN 3
#define MAKEFILE_CANNOT_CLOSE 4
#define MAKEFILE_CANNOT_ADD 5

// Variable names.
#define MAKEFILE_VARIABLE_TESTS "TESTS"
#define MAKEFILE_VARIABLE_RM_STUFF "RM_STUFF"
#define MAKEFILE_VARIABLE_TESTS_SRC_POSTFIX "_SRC"
#define MAKEFILE_VARIABLE_TESTS_OBJ_POSTFIX "_OBJ"
#define MAKEFILE_VARIABLE_TESTS_EXE_POSTFIX "_SRC"

// Print constants. User can customize these.
#define MAKEFILE_HEADER_LINE "# Mcgoo test framework makefile."
#define MAKEFILE_OBJ_CONVERT_FORMAT \
  "$(shell echo $(%s) | sed -E -e 's/([a-z\\-]+).c/$(BUILD_DIR)\\/\1.o/g')"

// Create a makefile will the filename.
// If the file is already created, it appends to it.
int MakefileCreate(const char *filename);

// Add a test.
// A test is like one C file with cases in it that you can call run() on.
int MakefileAddTest(const char *testName);

// Close the makefile. Don't forget to call this!
int MakefileClose(void);

#endif /* __MAKEFILE_H__ */
