//
// test.c
//
// Andrew Keesler
//
// October 13, 2014
//
// Test for mcgoo unit test framework.

#include <unit-test.h>
#include <unistd.h>

int numbersTest(void)
{
  expect(1 == 1);
  expect( 0xFF == 0xFF);
  expect(-1 == -1);
  expect( 1.1 == 1.1);
  return 0;
}

int stringsTest(void)
{
  expectString("andrew", "andrew");
  expectString("fAnTaStic1", "fAnTaStic1");
  return 0;
}

int longTest(void)
{
  sleep(2);
  return 0;
}

int noteTest(void)
{
  int hey;

  noteTime();

  expect(1); expect(1); expect(1);

  hey = 5;
  noteInt(hey);

  expect(1); expect(1); expect(1);

  hey = 10;
  noteInt(hey);

  expect(1); expect(1); expect(1);

  noteTime();

  hey = 129;
  noteHex(hey);

  expect(1); expect(1); expect(1);

  double ok = 1.123123123;
  noteFloat(ok);

  expect(1); expect(1); expect(1);

  note("andrew");

  noteTime();

  return 0;
}

int verboseTest(void)
{
  setVerbose(1);

  expect(1); expect(1); expect(1);
  expect(1); expect(1); expect(1);
  expect(1); expect(1); expect(1);

  usleep(123456);

  expect(1 + 3);
  expect(4 - 2 + 1 * 5);
  expect(!( 3 - 3));

  setVerbose(0);

  return 0;
}

int equalsTest(void)
{
  expect(1); expect(1); expect(1);
  expect(1); expect(1); expect(1);
  expect(1); expect(1); expect(1);
  
  expectEquals(1, 1);

  expectEquals(getpid(), getpid());

  expectEquals(1, 0);

  return 0;
}

static int handlerCalled = 0;
static void failureHandler(void)
{
  handlerCalled = 1;
}

int failedTest(void)
{
  int i;
  for (i = 1; i < 10; i ++)
    expect(i);
  expect(1 == 2);
  expect(!handlerCalled);
  setFailureHandler(failureHandler);
  expect(1 == 2);
  expect(handlerCalled);

  return 0;
}

int failedVerboseTest(void)
{
  setVerbose(1);

  expect(1); expect(1); expect(1);
  expect(1); expect(1); expect(1);
  expect(1); expect(1); expect(1);

  expect(1 + 3 - 2 - 2);

  setVerbose(0);

  return 0;
}

int main(void)
{
  announce();

  run(numbersTest);
  run(stringsTest);
  run(longTest);
  run(noteTest);
  run(verboseTest);
  run(equalsTest);
  
  run(failedTest);
  run(failedVerboseTest);

  return 0;
}
