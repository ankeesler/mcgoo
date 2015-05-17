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

static struct timeval testStart, testEnd;

static int expectNum = 0;
static void (*failureHandler)(void) = NULL;

int mcgooVerbose = 0;

static long timeDiffUS(struct timeval *start, struct timeval *end)
{
  return (((end->tv_sec * 1000000) + end->tv_usec)
          - ((start->tv_sec * 1000000) + start->tv_usec));
}
                       

void setFailureHandler(void (*fh)(void))
{
  failureHandler = fh;
}

void runTest(int (*test)(void), const char *name)
{
  int returnVal;

  expectNum = 0;
  printf("(test = %s)", name);
  printf(" [ ");
  fflush(stdout);

  gettimeofday(&testStart, NULL);
  returnVal = test();
  gettimeofday(&testEnd, NULL);

  printf(" ]");
  if (mcgooVerbose) {
    printf(" ( %ld us )\n%s\n",
           timeDiffUS(&testStart, &testEnd),
           (returnVal == 0 ? "PASS" : "FAIL"));
  }
  printf("\n");
  fflush(stdout);
}

void _expect(int comparison, const char *comparisonString, int line)
{
  if (comparison) {
    expectNum ++;
    if (mcgooVerbose) {
      gettimeofday(&testEnd, NULL);
      printf("\n  expect SUCCESS { %s } @ line %d ( %ld us )",
             comparisonString, line, timeDiffUS(&testStart, &testEnd));
    } else {
      printf(".");
    }
    fflush(stdout);
  } else {
    if (mcgooVerbose) {
      printf("\n  ");
    } else {
      printf("X <- %d ] ",
             expectNum);
    }
    printf("expect FAIL { %s } @ line %d",
           comparisonString, line);
#ifndef UNIT_TEST_UNIT_TEST
    printf("\n\n");
    fflush(stdout);
    if (failureHandler) failureHandler();
    exit(-1);
#endif
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
