//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#include "raylib.h"
#include "raymath.h"
#include <string.h>
#include <time.h>

#define DK_CONSOLE_IMPLEMENTATION
#include "dk_console.h"

static Console console = { .toggle_key = KEY_TAB };
static Console* console_global_ptr = NULL;

void CustomLog(int msgType, const char *text, va_list args)
  {
    static char buffer[1024] = {0};

    char timeStr[64] = {0};
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    vsprintf(buffer, text, args);

    char *finalBuffer = (char *)malloc(1024);
    memset(finalBuffer, 0, 1024);
    sprintf(finalBuffer, "%s %s", timeStr, buffer);

    const char *msgTypeStr = "Unknown";
    switch (msgType)
    {
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

    char *finalBuffer2 = (char *)malloc(1024);
    memset(finalBuffer2, 0, 1024);
    sprintf(finalBuffer2, "%s %s", msgTypeStr, finalBuffer);

    free(finalBuffer);

    if (console_global_ptr != NULL)
    {
      console_global_ptr->logs[console_global_ptr->log_index++] = (Log){.text = finalBuffer2, .type = msgType};
    }
  }


void console_handler(char *command)
{
  CustomLog(LOG_INFO, command, NULL);
}

int
main(void)
{

  SetTraceLogCallback(CustomLog);

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
  unsigned char *fileData = LoadFileData("Resources/font/JetBrainsMono-Regular.ttf", &fileSize);
  int fontSize = 128;

  imui.font = (Font*)malloc(sizeof(Font));
  imui.font->baseSize = fontSize;
  imui.font->glyphCount = 95;

  imui.font->glyphs = LoadFontData(fileData, fileSize, fontSize, 0, 0, FONT_SDF);
  Image atlas = GenImageFontAtlas(imui.font->glyphs, &imui.font->recs, imui.font->glyphCount, fontSize, 0, 1);
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
