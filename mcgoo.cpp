//
// mcgoo.cpp
// Andrew Keesler
// November 21, 2014
//
// Main mcgoo file.

#include <iostream>
#include <cstring>

using namespace std;

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
  if (argc < 2) {
    cout << "usage: mcgoo init" << endl;
    return 0;
  }

  for (int i = 0; i < argc; i ++) {
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
}
