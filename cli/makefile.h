//
// makefile.h
// Andrew Keesler
// November 22, 2014
//
// A makefile.

#ifndef __MAKEFILE_H__
#define __MAKEFILE_H__

#include <stdio.h>

// Errors.
#define MAKEFILE_SUCCESS 0
#define MAKEFILE_ALREADY_CREATED 1
#define MAKEFILE_CANNOT_OPEN 2

// Create a makefile will the filename.
int MakefileCreate(const char *filename);

#endif /* __MAKEFILE_H__ */
