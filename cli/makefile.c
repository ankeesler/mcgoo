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

  if (!(makefile = fopen(filename, "w")))
    return MAKEFILE_CANNOT_OPEN;

  return MAKEFILE_SUCCESS;
}
