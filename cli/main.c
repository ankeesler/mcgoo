//
// mcgoo.c
// Andrew Keesler
// November 21, 2014
//
// Main mcgoo file.

#include <stdio.h>
#include <string.h>

#include "makefile.h"

void initAction(void);

typedef struct {
  const char *command;
  void (*action)(void);
} CommandAction;

static CommandAction commandActions[] = {
  { "init", initAction },
  { NULL, NULL }
};

int main(int argc, char *argv[])
{
  int i;

  if (argc < 2) {
    printf("usage: mcgoo init\n");
    return 0;
  }

  for (i = 0; i < argc; i ++) {
    for (CommandAction *commandAction = commandActions;
         commandAction->command;
         commandAction ++) {
      if (!strcmp(argv[i], commandAction->command))
        (*commandAction->action)();
    }
  }

  return 0;
}

void initAction(void)
{
  int error = MakefileCreate("Mcgoo.mak");
  if (error)
    printf("Error: cannot create makefile: %d\n", error);
}
