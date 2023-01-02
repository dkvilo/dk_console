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

    DK_ConsoleUpdate(&console, &imui);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
