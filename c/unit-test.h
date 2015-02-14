//
// unit-test.h
//
// Andrew Keesler
// July 27, 2014
//
// Code for unit tests.
//

#ifndef __UNIT_TEST_H__ 
#define __UNIT_TEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** mcgoo c test framework
  
    It is recommended only to make ::expect() calls in the process
    from which the test was run. A failed expect in a child process
    can lead to misleading failure printouts and twisted wait() calls
    by the parent process.
*/

/** Run a test.
    @param test, The test to run
    @param name, The name of the test to run
*/
void runTest(int (*test)(void), const char *name);
#define run(test) runTest(test, #test)

/** Announce that a test from a file is running.
*/
void _announce(const char *);
#define announce() _announce(__FILE__)

void _expect(int, const char *, int);
/** Standard expect.

    @param comparison, comparison that you want to be true.
*/
#define expect(comparison) _expect(comparison, #comparison, __LINE__)

void _expectString(const char *, const char *, int);
/** Standard expect of strings.

    @param s1, The first string.
    @param s2, The second string.
*/
#define expectString(s1, s2) _expectString(s1, s2, __LINE__)

/** Print out a string during a test.

    @param string The string to print out.
*/
#define note(string)                                  \ 
  do {                                                \
    printf("(%s)", string);                           \
    fflush(stdout);                                   \
  } while(0);

/** Print out an variable's int value during a test.

    @param variable The variable you want to pring out.
*/
#define noteInt(variable)                             \
  do {                                                \
    printf("(%s = %d)", #variable, variable);         \
    fflush(stdout);                                   \
  } while(0);


/** Print out a variable in hex value during a test.

    @param variable The variable you want to pring out.
*/
#define noteHex(variable)                             \
  do {                                                \
    printf("(%s = 0x%X)", #variable, (long)variable); \
    fflush(stdout);                                   \
  } while(0);

/** Print out a variable as a float during a test.

    @param variable The variable you want to pring out.
*/
#define noteFloat(variable)                           \
  do {                                                \
    printf("(%s = %f)", #variable, (long)variable);   \
    fflush(stdout);                                   \
  } while(0);

#endif /* __BGE_MAP_TEST_H__ */

