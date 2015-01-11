//
// unit-test.c
//
// Andrew Keesler
// July 27, 2014
//
// Code for unit tests.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

static int expectNum = 0;

void runTest(int (*test)(void), const char *name)
{
  struct timeval testStart, testEnd;
  int returnVal;
  long timeDiffUS;

  expectNum = 0;
  printf("(test = %s)", name);
  printf(" [ ");
  fflush(stdout);

  gettimeofday(&testStart, NULL);
  returnVal = test();
  gettimeofday(&testEnd, NULL);
  timeDiffUS = (((testEnd.tv_sec * 1000000) + testEnd.tv_usec)
                - ((testStart.tv_sec * 1000000) + testStart.tv_usec));

  printf(" ] ( %ld us ) %s\n",
         timeDiffUS,
         returnVal == 0 ? "PASS" : "FAIL");
  fflush(stdout);
}

void _expect(int comparison, const char *comparisonString, int line)
{
  if (comparison) {
    expectNum ++;
    printf(".");
    fflush(stdout);
  } else {
    printf("X <- %d ] FAIL { %s } @ line %d\n",
           expectNum, comparisonString, line);
    printf("\n");
    fflush(stdout);
    exit(-1);
  }
}

void _expectString(const char *s1, const char *s2, int line)
{
#define EXPECT_STRING_THING_FORMAT "%s == %s"
  if ((strlen(s1) + 4 + strlen(s2)) <= 256) {
    char expectStringThing[256];
    sprintf(expectStringThing,
            EXPECT_STRING_THING_FORMAT,
            s1, s2);
    _expect(!strcmp(s1, s2), expectStringThing, line);
  } else {
    _expect(!strcmp(s1, s2), "s1 == s2", line);
  }
}

void _announce(const char *filename)
{
  printf("\n| *\n");
  printf("| * test : %s *|\n", filename);
  printf("| *\n");
  fflush(stdout);
}
