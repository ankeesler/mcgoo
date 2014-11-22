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
#define MAKEFILE_NOT_CREATED 2
#define MAKEFILE_CANNOT_OPEN 3
#define MAKEFILE_CANNOT_CLOSE 4

// Print constants. User can customize these.
#define MAKEFILE_HEADER_LINE "# Mcgoo test framework makefile."

// Create a makefile will the filename.
// If the file is already created, it appends to it.
int MakefileCreate(const char *filename);

// Close the makefile. Don't forget to call this!
int MakefileClose(void);

#endif /* __MAKEFILE_H__ */
