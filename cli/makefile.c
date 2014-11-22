//
// Makefile.cpp
// Andrew Keesler
// November 22, 2014
//
// A makefile.

#include "Makefile.h"

static FILE *makefile = NULL;

/*
  Private stuff.
 */


/*
  Public stuff.
 */
int MakefileCreate(const char *filename)
{
  if (makefile)
    return MAKEFILE_ALREADY_CREATED;

  if (!(makefile = fopen(filename, "w+")))
    return MAKEFILE_CANNOT_OPEN;

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