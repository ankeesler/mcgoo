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
const char *mcgooProgress = ".";

static long timeDiffUS(struct timeval *start, struct timeval *end) {
  return (((end->tv_sec * 1000000) + end->tv_usec) -
          ((start->tv_sec * 1000000) + start->tv_usec));
}

void setFailureHandler(void (*fh)(void)) { failureHandler = fh; }

void runTest(int (*test)(void), const char *name) {
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
    printf(" ( %ld us )\n%s\n", timeDiffUS(&testStart, &testEnd),
           (returnVal == 0 ? "PASS" : "FAIL"));
  }
  printf("\n");
  fflush(stdout);
}

void _expect(int comparison, const char *comparisonString, int line) {
  if (comparison) {
    expectNum++;
    if (mcgooVerbose) {
      gettimeofday(&testEnd, NULL);
      printf("\n  expect SUCCESS { %s } @ line %d ( %ld us )", comparisonString,
             line, timeDiffUS(&testStart, &testEnd));
    } else {
      printf("%s", mcgooProgress);
    }
    fflush(stdout);
  } else {
    if (mcgooVerbose) {
      printf("\n  ");
    } else {
      printf("X <- %d ] ", expectNum);
    }
    printf("expect FAIL { %s } @ line %d", comparisonString, line);
#ifndef UNIT_TEST_UNIT_TEST
    printf("\n\n");
    fflush(stdout);
    if (failureHandler)
      failureHandler();
    exit(-1);
#endif
  }
}

void _expectString(const char *s1, const char *s2, int line) {
#define EXPECT_STRING_THING_FORMAT "%s == %s"
  if ((strlen(s1) + 4 + strlen(s2)) <= 256) {
    char expectStringThing[256];
    sprintf(expectStringThing, EXPECT_STRING_THING_FORMAT, s1, s2);
    _expect(!strcmp(s1, s2), expectStringThing, line);
  } else {
    _expect(!strcmp(s1, s2), "s1 == s2", line);
  }
}

void _expectEquals(long val1, long val2, int line) {
  char expectStringThing[256];
  sprintf(expectStringThing, "0x%lX == 0x%lX", val1, val2);
  _expect(val1 == val2, expectStringThing, line);
}

void _announce(const char *filename) {
  printf("\n| *\n");
  printf("| * test : %s *|\n", filename);
  printf("| *\n");
  fflush(stdout);
}

void noteTime(void) {
  struct timeval currentTime;
  char buffer[0xFF];
  int end, spaces, index;

  gettimeofday(&currentTime, NULL);

  memset(buffer, 0, 0xFF);
  sprintf(buffer, "%ld",
          ((currentTime.tv_sec * 1000000) + currentTime.tv_usec));

  end = strlen(buffer) - 1;
  spaces = end / 3;
  index = spaces + end;
  while (end >= 3) {
    buffer[index - 0] = buffer[end - 0];
    buffer[index - 1] = buffer[end - 1];
    buffer[index - 2] = buffer[end - 2];
    buffer[index - 3] = ' ';

    end -= 3;
    spaces = end / 3;
    index = spaces + end;
  }

  printf("%s(time = %s)", (mcgooVerbose ? "\n  " : ""), buffer);
}
