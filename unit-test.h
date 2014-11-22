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

/** Standard expect.

    @param comparison, comparison that you want to be true.
*/
void _expect(int, const char *);
#define expect(comparison) _expect(comparison, #comparison)

/** Standard expect of strings.

    @param s1, The first string.
    @param s2, The second string.
*/
void expectString(const char *s1, const char *s2);

#endif /* __BGE_MAP_TEST_H__ */
