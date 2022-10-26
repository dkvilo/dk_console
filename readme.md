# Dev Console

DK Console is a super simple drop in dev console for your raylib game/engine.

## Building Examples

```bash
  make && ./console
```

<img src="https://github.com/dkvilo/dk_console/blob/master/Resources/prev.png" />

## Usage

1. Copy the `dk_console.h` and `dk_ui.h` files into your project.
2. Include the header in your main file.

## Example

```c
#include "raylib.h"

#define DK_CONSOLE_IMPLEMENTATION
#include "dk_console.h"

#define LOG_SIZE 1024 * 1024
static Console console = { .toggle_key = KEY_TAB };

void
CustomLog(int msgType, const char* text, va_list args)
{
  char buffer[1024] = { 0 };
  vsprintf(buffer, text, args);
  strcpy(console.logs[++console.log_index].text, buffer);
}

int main(void)
{
  // Write Raylib logs to the console
  SetTraceLogCallback(CustomLog);

  // Initialize the ImUI context
  ImUI imui;
  imui.theme = &DK_ImUISolarizedTheme;
  imui.style = &DK_ImUIDefaultStyle;

  // Initialize the console context
  // Init Console before InitWindow to avoid race condition
  DK_ConsoleInit(&console, &imui, LOG_SIZE);

  // Initialize the window
  InitWindow(800, 450, "DK Console");

  // Set target FPS to 60 frames-per-second
  SetTargetFPS(60);

  // Load font in ImUI
  Font f = LoadFont("Resources/font/JetBrainsMono-Regular.ttf");
  imui.font = &f;
  imui.font->baseSize = 30;
  imui.font->glyphCount = 95;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKGRAY);
    // Update and Draw Console
    DK_ConsoleUpdate(&console, &imui);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

```
