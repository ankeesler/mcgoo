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

  expect(1); expect(1); expect(1);

  hey = 5;
  noteInt(hey);

  expect(1); expect(1); expect(1);

  hey = 10;
  noteInt(hey);

  expect(1); expect(1); expect(1);

  hey = 129;
  noteHex(hey);

  expect(1); expect(1); expect(1);

  double ok = 1.123123123;
  noteFloat(ok);

  return 0;
}

int failedTest(void)
{
  int i;
  for (i = 1; i < 10; i ++)
    expect(i);
  expect(1 == 2);
  return 0;
}

int main(void)
{
  announce();
  run(numbersTest);
  run(stringsTest);
  run(longTest);
  run(noteTest);
  run(failedTest);
  return 0;
}
