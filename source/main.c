//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#include "raylib.h"
#include "raymath.h"
#include <string.h>
#include <time.h>
#include <assert.h>

#define DK_CONSOLE_IMPLEMENTATION
#include "dk_console.h"

#define DK_CONSOLE_EXT_COMMAND_IMPLEMENTATION
#include "dk_command.h"

static Console console = { .toggle_key = KEY_TAB };
static Console* console_global_ptr = NULL;

void
CustomLog(int msgType, const char* text, va_list args)
{
  assert(console_global_ptr != NULL);
  static char buffer[1024] = { 0 };

  char timeStr[64] = { 0 };
  time_t now = time(NULL);
  struct tm* tm_info = localtime(&now);

  strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
  vsprintf(buffer, text, args);

  char* finalBuffer = (char*)malloc(1024);
  memset(finalBuffer, 0, 1024);
  sprintf(finalBuffer, "%s %s", timeStr, buffer);

  const char* msgTypeStr = "Unknown";
  switch (msgType) {
    case 2:
      msgTypeStr = "(Debug)";
      break;
    case 3:
      msgTypeStr = "(Info)";
      break;
    case 4:
      msgTypeStr = "(Warning)";
      break;
    case 5:
      msgTypeStr = "(Error)";
      break;
    case 6:
      msgTypeStr = "(Fatal)";
      break;
  }

  char* finalBuffer2 = (char*)malloc(1024);
  memset(finalBuffer2, 0, 1024);
  sprintf(finalBuffer2, "%s %s", msgTypeStr, finalBuffer);

  free(finalBuffer);

  if (console_global_ptr != NULL) {
    console_global_ptr->logs[console_global_ptr->log_index++] =
      (Log){ .text = finalBuffer2, .type = msgType };
  }
}

void echo(char* argv)
{
  CustomLog(LOG_INFO, argv, NULL);
}

void clear(char* argv)
{
  DK_ConsoleClear(console_global_ptr);
}

void help(char* args)
{
  DK_ExtCommand* command_list = DK_ExtGetCommandsList();
  if (args != NULL && strlen(args) > 0) {
    for (int i = 0; i < DK_COMMAND_SIZE; i++)
    {
      if (command_list[i].name != NULL)
      {
        if (strcmp(command_list[i].name, args) == 0)
        {
          CustomLog(LOG_INFO, TextFormat("\t\t`%s`\t\t%s\n", command_list[i].name, command_list[i].help), NULL);
          if (command_list[i].argc > 0) {
            CustomLog(LOG_INFO, TextFormat("\t\ttakes %d argument(s)\n", command_list[i].argc), NULL);
          }
          break;
        }
      }
    }
    return;
  } else {
    CustomLog(LOG_INFO, "******************** HELP ********************", NULL);
    for (int i = 0; i < DK_COMMAND_SIZE; i++)
    {
      if (command_list[i].name != NULL)
      {
        CustomLog(LOG_INFO, TextFormat("\t\t`%s`\t\t%s\n", command_list[i].name, command_list[i].help), NULL);
        if (command_list[i].argc > 0) {
          CustomLog(LOG_INFO, TextFormat("\t\ttakes %d argument(s)\n", command_list[i].argc), NULL);
        }
        CustomLog(LOG_INFO, "----------------------------------------------", NULL);
      }
    }
  }
}

void
console_handler(char* command)
{

  char* command_buff = (char*)malloc(strlen(command) + 1);
  strcpy(command_buff, command);
  command_buff[strlen(command)] = '\0';

  char* token = strtok(command_buff, " ");

  char* message_buff = (char*)malloc(strlen(command) + 1);
  strcpy(message_buff, command);
  message_buff[strlen(command)] = '\0';

  char* message = strstr(message_buff, token) + strlen(token);
  while (*message == ' ') { message++; }

  if (!DK_ExtCommandExecute(token, message)) {
    CustomLog(LOG_ERROR, TextFormat("Unknown command `%s`", command), NULL);
  }

  free(command_buff);
  free(message_buff);
}

int
main(void)
{

  SetTraceLogCallback(CustomLog);

  DK_ExtCommandInit();
  DK_ExtCommandPush("echo", 1, "Prints a provided message in the console `echo Hello World`", &echo);
  DK_ExtCommandPush("clear", 0, "Clears the console buffer", &clear);
  DK_ExtCommandPush("help", 1, "Shows the available commands and/or specific one `help <command_name>`", &help);

  static ImUI imui;
  imui.theme = &DK_ImUISolarizedTheme;
  imui.style = &DK_ImUIDefaultStyle;

  const int screenWidth = 1280;
  const int screenHeight = 720;

  console_global_ptr = &console;

  DK_ConsoleInit(console_global_ptr, LOG_SIZE);
  InitWindow(screenWidth, screenHeight, "Dev Console");

  SetTargetFPS(60);

  unsigned int fileSize = 0;
  unsigned char* fileData =
    LoadFileData("Resources/font/JetBrainsMono-Regular.ttf", &fileSize);
  int fontSize = 128;

  imui.font = (Font*)malloc(sizeof(Font));
  imui.font->baseSize = fontSize;
  imui.font->glyphCount = 95;

  imui.font->glyphs =
    LoadFontData(fileData, fileSize, fontSize, 0, 0, FONT_SDF);
  Image atlas = GenImageFontAtlas(
    imui.font->glyphs, &imui.font->recs, imui.font->glyphCount, fontSize, 0, 1);
  imui.font->texture = LoadTextureFromImage(atlas);

  UnloadImage(atlas);
  UnloadFileData(fileData);
  SetTextureFilter(imui.font->texture, TEXTURE_FILTER_BILINEAR);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(Fade(BLACK, 0.5f));

    // Draw text
    DrawTextEx(*imui.font,
               "Press TAB to toggle the console",
               (Vector2){ 20.0f, 20.0f },
               20.0f,
               1.0f,
               GRAY);

    DK_ConsoleUpdate(console_global_ptr, &imui, console_handler);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
