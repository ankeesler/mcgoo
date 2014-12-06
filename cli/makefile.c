//
// Makefile.cpp
// Andrew Keesler
// November 22, 2014
//
// A makefile.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Makefile.h"

static FILE *makefile = NULL;

// Makefile stuff.
#define MAKEFILE_TEMPLATE_FILE "res/TemplateMakefile.mak"
#define MAKEFILE_TEMP_FILE "tmp.mak"

/*
  Private stuff.
 */

const char *getUppercase(const char *s)
{
  char *su = (char *)malloc(sizeof(char) * strlen(s));
  char *c = su;
  while (s) *c++ = toupper(*s++);
  return su;
}

// Splits at '='.
void getKeyValue(char *key, int *keySize, char *value, int *valueSize, FILE *stream)
{
  char c;
  
  *keySize = *valueSize = 0;
  
  do {
    c = fgetc(stream);
    
    switch(c) {
    case '=':
      key[*keySize++] = '\0';
      break;
    case '\n':
    case EOF:
      key[*keySize++] = '\0';
      return;
    default:
      key[*keySize++] = c;
    }
  } while (1);
  
  do {
    c = fgetc(stream);
    
    switch(c) {
    case '\n':
    case EOF:
      value[*valueSize++] = '\0';
      return;
    default:
      value[*valueSize++] = c;
    }
  } while (1);
}


/*
  Public stuff.
 */
int MakefileCreate(const char *filename)
{
  FILE *makefile = NULL;
  FILE *template = NULL;
  char c;
  
  if (makefile)
    return MAKEFILE_ALREADY_CREATED;

  if (!(makefile = fopen(filename, "w+")))
    return MAKEFILE_CANNOT_OPEN;
  
  if (!(template = fopen(MAKEFILE_TEMPLATE_FILE, "r")))
    return MAKEFILE_CANNOT_OPEN;
  
  // Copy template.
  while ((c = fgetc(template)) != EOF)
    fputc(c, makefile);

  return MAKEFILE_SUCCESS;
}

int MakefileAddTest(const char *testName)
{
  char c;
  const char *testNameUppercase;
  char key[0xFF], value[0xFF];
  int keySize, valueSize;
  FILE *temp;
  
  makefile = fopen(MAKEFILE_DEFAULT_NAME, "w+");
  temp = fopen(MAKEFILE_TEMP_FILE, "w");
  
  if (!makefile  || !temp || !testName)
    return MAKEFILE_CANNOT_ADD;
  
  testNameUppercase = getUppercase(testName);
  
  // Append to the tests key.
  do {
    getKeyValue(key, &keySize, value, &valueSize, makefile);
    if (!valueSize) {
      // Just write the line.
      fwrite(key, sizeof(char), keySize, temp);
    } else if (!strcmp(key, MAKEFILE_VARIABLE_TESTS)) {
      // Write the key. Write the value. Write the new value.
      fwrite(key, sizeof(char), keySize, temp);
      fwrite(value, sizeof(char), valueSize, temp);
      fprintf(temp, "%s \n", testName);
    }
  } while (keySize);
  
  // Scroll to end of the temp file. Setup the test.
  fseek(temp, 0, SEEK_END);
  fprintf(temp, "\n%s%s=\n", testNameUppercase, MAKEFILE_VARIABLE_TESTS_SRC_POSTFIX);
  fprintf(temp, "%s%s=", testNameUppercase, MAKEFILE_VARIABLE_TESTS_OBJ_POSTFIX);
  fprintf(temp, MAKEFILE_OBJ_CONVERT_FORMAT, testNameUppercase);
  fprintf(temp, "\n%s%s=\n", testNameUppercase, MAKEFILE_VARIABLE_TESTS_EXE_POSTFIX);
  fflush(temp);
  free((void*)testNameUppercase);
  
  // Copy over to the makefile.
  fseek(temp, 0, SEEK_SET);
  fseek(makefile, 0, SEEK_SET);
  while ((c = fgetc(temp)) != EOF)
    fputc(c, makefile);
  
  return MAKEFILE_SUCCESS;
}

int MakefileClose(void)
{
  int retVal = MAKEFILE_SUCCESS;
  
  if (!makefile)
    retVal = MAKEFILE_NOT_CREATED;
  else
    retVal = (fclose(makefile) ? MAKEFILE_CANNOT_CLOSE : MAKEFILE_SUCCESS);
  
  makefile = NULL;
  
  return retVal;
}