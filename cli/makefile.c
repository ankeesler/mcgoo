//
// Makefile.cpp
// Andrew Keesler
// November 22, 2014
//
// A makefile.

#include "Makefile.h"

// Here is the makefile.
static FILE *makefile = NULL;

// Makefile stuff.
#define MAKEFILE_TEMPLATE_FILE "res/TemplateMakefile.mak"

/*
  Private stuff.
 */


/*
  Public stuff.
 */
int MakefileCreate(const char *filename)
{
  FILE *template = NULL;
  char c;
  
  if (makefile)
    return MAKEFILE_ALREADY_CREATED;

  if (!(makefile = fopen(filename, "w+")))
    return MAKEFILE_CANNOT_OPEN;
  
  if (!(template = fopen(MAKEFILE_TEMPLATE_FILE, "r")))
    return MAKEFILE_CANNOT_OPEN;
  
  while ((c = fgetc(template)) != EOF)
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