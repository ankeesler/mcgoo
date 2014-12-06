//
// mcgoo.c
// Andrew Keesler
// November 21, 2014
//
// Main mcgoo file.

#include <stdio.h>
#include <string.h>

#include "makefile.h"

#define PRINT_USAGE() \
  printf("usage: mcgoo init [makefile_name]\n"); \
  printf("       mcgoo add test_name]\n");

void initAction(void *);
void addAction(void *);

typedef struct {
  const char *command;
  void (*action)(void *);
} CommandAction;

static CommandAction commandActions[] = {
  { "init", initAction },
  { "add",  addAction },
  { NULL, NULL }
};

int main(int argc, char *argv[])
{
  int i;

  if (argc < 2) {
    PRINT_USAGE();
    return 0;
  }

  for (i = 0; i < argc; i ++) {
    for (CommandAction *commandAction = commandActions;
         commandAction->command;
         commandAction ++) {
      if (!strcmp(argv[i], commandAction->command))
        (*commandAction->action)((argc > 2 ? argv[2] : NULL));
    }
  }

  return 0;
}

void initAction(void *data)
{
  int error = MakefileCreate(MAKEFILE_DEFAULT_NAME);
  if (error)
    printf("Error: cannot create makefile: %d\n", error);
  MakefileClose();
}

void addAction(void *data)
{
  int error = MakefileAddTest((const char *)data);
  if (error)
    printf("Error: cannot add test: %d\n", error);
  MakefileClose();
}