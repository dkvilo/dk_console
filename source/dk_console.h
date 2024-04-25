//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#if !defined(DK_CONSOLE_H)
#define DK_CONSOLE_H

#if defined(__cplusplus)
extern "C"
{
#endif

#include <stdlib.h> // malloc

#if defined(DK_CONSOLE_IMPLEMENTATION)
#define DK_UI_IMPLEMENTATION
#include "dk_ui.h"
#else
#include "dk_ui.h"
#endif

#if !defined(LOG_SIZE)
#define LOG_SIZE 1080 * 1080 // size of log buffer
#endif

  typedef struct
  {
    char* text;
    int type;
  } Log;

  typedef struct
  {
    int log_index;
    Log* logs;
    Rectangle ui;
    bool is_open;
    int scroll;
    KeyboardKey toggle_key;
  } Console;

  void DK_ConsoleInit(Console* console, int log_size);

  void DK_ConsoleUpdate(Console* console, ImUI* imui, void (*callback)(const char*));

  void DK_ConsoleShutdown(Console* console, int log_size);

#if defined(DK_CONSOLE_IMPLEMENTATION)
  void DK_ConsoleInit(Console* console, int log_size)
  {
    console->ui = (Rectangle){ 0.0f, 0.0f, 0.0f, 0.0f };
    console->ui.height = GetScreenHeight();
    console->is_open = false;
    console->log_index = 0;
    console->scroll = 0;
    console->logs = (Log*)malloc(sizeof(Log) * log_size);
    for (int i = 0; i < log_size; i++) {
      console->logs[i].text = (char*)malloc(1024);
      memset(console->logs[i].text, 0, 1024);
    }
  }

  void DK_ConsoleUpdate(Console* console, ImUI* imui, void (*callback)(const char*))
  {

    if (IsKeyPressed(console->toggle_key)) {
      console->is_open = !console->is_open;
    }

    static bool focused = false;

    if (console->is_open) {
      console->ui.height =
        Clamp(Lerp(console->ui.height, GetScreenHeight(), 0.5f),
              0.0f,
              GetScreenHeight());
      focused = true;
    } else {
      console->ui.height = Lerp(console->ui.height, 0.0f, 0.5f);
    }

    // Console Background
    DrawRectangle(0,
                  0,
                  GetScreenWidth(),
                  console->ui.height,
                  Fade(imui->theme->background, 1.0f));

    if (console->is_open) {

      static bool dp_is_open = false;
      static int dp_selected = 0;

#define DP_OPTIONS_COUNT 7

      static char* dp_options[DP_OPTIONS_COUNT] = {
        "Solarized", "Dark", "Light", "Default", "Nord", "Monkai", "White",
      };

      Vector2 dp_pos = { (float)GetScreenWidth() - 130.0f, 10.f };
      float dp_width = 120.0f;
      float dp_height = 20.0f;

      static int dp_status = 0;
      dp_status = DK_DrawDropdown(imui,
                                  dp_pos,
                                  dp_width,
                                  dp_height,
                                  dp_options[dp_selected],
                                  dp_options,
                                  DP_OPTIONS_COUNT,
                                  &dp_selected,
                                  &dp_is_open);
      if (dp_status) {
        switch (dp_selected) {
          case 0:
            imui->theme = &DK_ImUISolarizedTheme;
            break;
          case 1:
            imui->theme = &DK_ImUIDarkTheme;
            break;
          case 2:
            imui->theme = &DK_ImUILightTheme;
            break;
          case 3:
            imui->theme = &DK_ImUIDefaultTheme;
            break;
          case 4:
            imui->theme = &DK_ImUINordTheme;
            break;
          case 5:
            imui->theme = &DK_ImUIMonokaiTheme;
            break;
          case 6:
            imui->theme = &DK_ImUIWhiteTheme;
            break;
        }
      }

#undef DP_OPTIONS_COUNT

      Rectangle DrawingTextArea = {
        0.0f, 0.0f, (float)GetScreenWidth(), console->ui.height
      };

      int scroll_step = 1;
      int min_scroll_val = 0;

      if (focused) {
        if (IsKeyDown(KEY_DOWN)) {
          console->scroll += scroll_step;
        } else if (IsKeyDown(KEY_UP)) {
          console->scroll -= scroll_step;
        }
      }

      if (CheckCollisionPointRec(GetMousePosition(), DrawingTextArea)) {
        if (GetMouseWheelMove() > 0) {
          console->scroll += scroll_step;
        } else if (GetMouseWheelMove() < 0) {
          console->scroll -= scroll_step;
        }
      }

      console->scroll =
        Clamp(console->scroll, min_scroll_val, console->log_index);

      static int scroll_offset = 0;
      int real_scroll = ((console->log_index - console->scroll) * 30);

      scroll_offset = real_scroll;
      scroll_offset =
        Clamp((float)scroll_offset,
              0.0f,
              (console->log_index * 30.0f) - (console->ui.height - 30.0f));

      // Colors array based on log type
      Color colors[4] = {
        GRAY,              // debug
        ORANGE,            // warning
        RED,               // error
        imui->theme->text, // info
      };

      for (int i = 0; i < console->log_index; i++) {
        Vector2 pos = { 10, 0 - scroll_offset + (float)i * 30 };
        if (pos.y > console->ui.height - 45)
          break;
        if (console->logs[i].type == LOG_INFO) {
          DrawTextEx(*imui->font, console->logs[i].text, pos, 20, 1, colors[3]);
        } else if (console->logs[i].type == LOG_WARNING) {
          DrawTextEx(*imui->font, console->logs[i].text, pos, 20, 1, colors[1]);
        } else if (console->logs[i].type == LOG_ERROR) {
          DrawTextEx(*imui->font, console->logs[i].text, pos, 20, 1, colors[2]);
        } else if (console->logs[i].type == LOG_DEBUG) {
          DrawTextEx(*imui->font, console->logs[i].text, pos, 20, 1, colors[0]);
        }
      }

      static char text[1024] = "";
      Vector2 input_pos = { 0.0f, console->ui.height - 31.0f };
      DK_DrawInputField(imui, input_pos, GetScreenWidth(), 30, text, &focused, NULL);

      if (IsKeyPressed(KEY_ENTER)) {
        if (strlen(text) > 0) {
          if (console->log_index >= LOG_SIZE) {
            console->log_index = 0;
          }

          if (callback != NULL) {
            callback(text);
          }

          strcpy(text, "");
        }
      }
    }
  }

  void DK_ConsoleClear(Console* console)
  {
    console->log_index = 0;
    console->scroll = 0;
  }

  void DK_ConsoleShutdown(Console* console, int log_size) {
    for (int i = 0; i < log_size; i++) {
      free(console->logs[i].text);
    }
    free(console->logs);
  }

#endif

#if defined(__cplusplus)
}
#endif

#endif // DK_CONSOLE_H
