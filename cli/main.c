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
  printf("usage: mcgoo init [makefile name]\n");

void initAction(void *);

typedef struct {
  const char *command;
  void (*action)(void *);
} CommandAction;

static CommandAction commandActions[] = {
  { "init", initAction },
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
  int error = MakefileCreate((data ? "Mcgoo.mak" : "Mcgoo.mak"));
  if (error)
    printf("Error: cannot create makefile: %d\n", error);
  MakefileClose();
}
