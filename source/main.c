//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#include "raylib.h"
#include "raymath.h"
#include <string.h>

#define DK_CONSOLE_IMPLEMENTATION
#include "dk_console.h"

#define LOG_SIZE 1024 * 1024
static Console console = { .toggle_key = KEY_TAB };

// Custom log function to send logs to the console
void
CustomLog(int msgType, const char* text, va_list args)
{
  char buffer[1024] = { 0 };
  vsprintf(buffer, text, args);
  strcpy(console.logs[++console.log_index].text, buffer);
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

  DK_ConsoleInit(&console, LOG_SIZE);
  InitWindow(screenWidth, screenHeight, "Dev Console");

  SetTargetFPS(60);

  Font f = LoadFont("Resources/font/JetBrainsMono-Regular.ttf");
  imui.font = &f;
  imui.font->baseSize = 30;
  imui.font->glyphCount = 95;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(Fade(BLACK, 0.5f));

    // Draw text
    DrawTextEx(*imui.font,
               "Press TAB to toggle the console",
               (Vector2){ 20.0f, 20.0f },
               imui.font->baseSize,
               2,
               GRAY);

    DK_ConsoleUpdate(&console, &imui);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
