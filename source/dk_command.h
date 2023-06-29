#if !defined(DK_CONSOLE_EXT_COMMAND_H)
#define DK_CONSOLE_EXT_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#if !defined(DK_COMMAND_SIZE)
#define DK_COMMAND_SIZE 100
#endif

typedef struct
{
  char *name;
  int argc;
  char *help;
  void (*func)(const char*);
} DK_ExtCommand;

static DK_ExtCommand* dk_commands_list = NULL;

DK_ExtCommand* DK_ExtGetCommandsList();

void DK_ExtCommandInit();

void DK_ExtCommandPush(char *name, int argc, char *help, void (*func)(const char*));

bool DK_ExtCommandExecute(char *name, char *args);

void DK_ExtCommandFree();

#if defined(DK_CONSOLE_EXT_COMMAND_IMPLEMENTATION)

DK_ExtCommand* DK_ExtGetCommandsList()
{
  assert(dk_commands_list != NULL);
  return dk_commands_list;
}

void DK_ExtCommandInit()
{
  dk_commands_list = (DK_ExtCommand*)malloc(sizeof(DK_ExtCommand) * DK_COMMAND_SIZE);
  memset(dk_commands_list, 0, sizeof(DK_ExtCommand) * DK_COMMAND_SIZE);
}

void DK_ExtCommandPush(char *name, int argc, char *help, void (*func)(const char*))
{
  for (int i = 0; i < DK_COMMAND_SIZE; i++)
  {
    if (dk_commands_list[i].name == NULL)
    {
      dk_commands_list[i].name = name;
      dk_commands_list[i].argc = argc;
      dk_commands_list[i].help = help;
      dk_commands_list[i].func = func;
      break;
    }
  }
}

bool DK_ExtCommandExecute(char *name, char *args)
{
  for (int i = 0; i < DK_COMMAND_SIZE; i++)
  {
    if (dk_commands_list[i].name != NULL)
    {
      if (strcmp(dk_commands_list[i].name, name) == 0)
      {
        dk_commands_list[i].func(args);
        break;
      }
    } else {
      return false;
    }
  }
  return true;
}

void DK_ExtCommandFree()
{
  free(dk_commands_list);
}

#endif // DK_CONSOLE_EXT_COMMAND_IMPLEMENTATION

#endif // DK_CONSOLE_EXT_COMMAND_H
