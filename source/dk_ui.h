//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#if !defined(DK_UI_H)
#define DK_UI_H

#if defined(__cplusplus)
extern "C"
{
#endif

#if !defined(RAYLIB_H)
#include "raylib.h"
#endif

#include <math.h>   // floorf, ceilf, roundf
#include <stdio.h>  // sprintf
#include <string.h> // strlen, strcpy, strcat

  typedef struct ImUITheme
  {
    Color background;
    Color text;
    Color button;
    Color buttonHover;
    Color buttonActive;
    Color toggle;
    Color toggleHover;
    Color toggleCursor;
    Color select;
    Color selectActive;
    Color slider;
    Color sliderCursor;
    Color sliderCursorHover;
    Color sliderCursorActive;
    Color property;
    Color border;
    Color textFiledCursor;
    Color textFiledSelection;
    Color optionText;
    Color optionBackground;
    Color optionHover;
  } ImUITheme;

  typedef struct ImUIStyle
  {
    int borderSize;
    float roundness;
  } ImUIStyle;

  typedef struct ImUI
  {
    Font* font;
    ImUITheme* theme;
    ImUIStyle* style;
  } ImUI;

  static ImUIStyle DK_ImUIDefaultStyle = {
    .borderSize =         1,
    .roundness  =       0.0f,
  };

  // @Default theme (dark)
  static ImUITheme DK_ImUIDefaultTheme = {
   .background =           { 50, 50, 50, 255 },
   .text =                 { 255, 255, 255, 255 },
   .button =               { 50, 50, 50, 255 },
   .buttonHover =          { 60, 60, 60, 255 },
   .buttonActive =         { 60, 60, 60, 255 },
   .toggle =               { 60, 60, 60, 255 },
   .toggleHover =          { 70, 70, 70, 255 },
   .toggleCursor =         { 80, 80, 80, 255 },
   .select =               { 60, 60, 60, 255 },
   .selectActive =         { 60, 60, 60, 255 },
   .slider =               { 50, 50, 50, 255 },
   .sliderCursor =         { 80, 80, 80, 255 },
   .sliderCursorHover =    { 80, 80, 80, 255 },
   .sliderCursorActive =   { 80, 80, 80, 255 },
   .property =             { 50, 50, 50, 255 },
   .border =               { 60, 60, 60, 255 },
   .textFiledCursor =      { 0, 228, 48, 255 },
   .textFiledSelection =   { 0, 117, 44, 255 },
   .optionText =           { 255, 255, 255, 255 },
   .optionBackground =     { 50, 50, 50, 255 },
   .optionHover =          { 60, 60, 60, 255 },
  };

  // @Solarized theme
  static ImUITheme DK_ImUISolarizedTheme = {
   .background =           { 0, 43, 54, 255 },
   .text =                 { 131, 148, 150, 255 },
   .button =               { 7, 54, 66, 255 },
   .buttonHover =          { 88, 110, 117, 255 },
   .buttonActive =         { 88, 110, 117, 255 },
   .toggle =               { 7, 54, 66, 255 },
   .toggleHover =          { 88, 110, 117, 255 },
   .toggleCursor =         { 101, 123, 131, 255 },
   .select =               { 7, 54, 66, 255 },
   .selectActive =         { 88, 110, 117, 255 },
   .slider =               { 7, 54, 66, 255 },
   .sliderCursor =         { 101, 123, 131, 255 },
   .sliderCursorHover =    { 88, 110, 117, 255 },
   .sliderCursorActive =   { 101, 123, 131, 255 },
   .property =             { 7, 54, 66, 255 },
   .border =               { 101, 123, 131, 255 },
   .textFiledCursor =      { 0, 228, 48, 255 },
   .textFiledSelection =   { 0, 0, 0, 100 },
   .optionText =           { 131, 148, 150, 255 },
   .optionBackground =     { 7, 54, 66, 255 },
   .optionHover =          { 88, 110, 117, 255 },
  };

  // @Light theme
  static ImUITheme DK_ImUILightTheme = {
    .background =           { 210, 210, 210, 255 },
    .text =                 { 50, 50, 50, 255 },
    .button =               { 200, 200, 200, 255 },
    .buttonHover =          { 175, 175, 175, 255 },
    .buttonActive =         { 175, 175, 175, 255 },
    .toggle =               { 200, 200, 200, 255 },
    .toggleHover =          { 175, 175, 175, 255 },
    .toggleCursor =         { 50, 50, 50, 255 },
    .select =               { 200, 200, 200, 255 },
    .selectActive =         { 175, 175, 175, 255 },
    .slider =               { 200, 200, 200, 255 },
    .sliderCursor =         { 50, 50, 50, 255 },
    .sliderCursorHover =    { 50, 50, 50, 255 },
    .sliderCursorActive =   { 50, 50, 50, 255 },
    .property =             { 200, 200, 200, 255 },
    .border =               { 175, 175, 175, 255 },
    .textFiledCursor =      { 0, 228, 48, 255 },
    .textFiledSelection =   { 0, 117, 44, 255 },
    .optionText =           { 200, 200, 200, 255 },
    .optionBackground =     { 175, 175, 175, 255 },
    .optionHover =          { 50, 50, 50, 255 },
  };

  // @Dark theme
  static ImUITheme DK_ImUIDarkTheme = {
    .background =           { 45, 45, 45, 255 },
    .text =                 { 235, 235, 235, 255 },
    .button =               { 60, 60, 60, 255 },
    .buttonHover =          { 75, 75, 75, 255 },
    .buttonActive =         { 75, 75, 75, 255 },
    .toggle =               { 60, 60, 60, 255 },
    .toggleHover =          { 75, 75, 75, 255 },
    .toggleCursor =         { 175, 175, 175, 255 },
    .select =               { 60, 60, 60, 255 },
    .selectActive =         { 75, 75, 75, 255 },
    .slider =               { 60, 60, 60, 255 },
    .sliderCursor =         { 175, 175, 175, 255 },
    .sliderCursorHover =    { 175, 175, 175, 255 },
    .sliderCursorActive =   { 175, 175, 175, 255 },
    .property =             { 60, 60, 60, 255 },
    .border =               { 75, 75, 75, 255 },
    .textFiledCursor =      { 0, 228, 48, 255 },
    .textFiledSelection =   { 0, 117, 44, 255 },
    .optionText =           { 60, 60, 60, 255 },
    .optionBackground =     { 75, 75, 75, 255 },
    .optionHover =          { 175, 175, 175, 255 },
  };

  // @Monokai theme
  static ImUITheme DK_ImUIMonokaiTheme = {
   .background =           { 39, 40, 34, 255 },
   .text =                 { 248, 248, 242, 255 },
   .button =               { 50, 50, 50, 255 },
   .buttonHover =          { 75, 75, 75, 255 },
   .buttonActive =         { 75, 75, 75, 255 },
   .toggle =               { 50, 50, 50, 255 },
   .toggleHover =          { 75, 75, 75, 255 },
   .toggleCursor =         { 175, 175, 175, 255 },
   .select =               { 50, 50, 50, 255 },
   .selectActive =         { 75, 75, 75, 255 },
   .slider =               { 50, 50, 50, 255 },
   .sliderCursor =         { 175, 175, 175, 255 },
   .sliderCursorHover =    { 175, 175, 175, 255 },
   .sliderCursorActive =   { 175, 175, 175, 255 },
   .property =             { 50, 50, 50, 255 },
   .border =               { 75, 75, 75, 255 },
   .textFiledCursor =      { 0, 228, 48, 255 },
   .textFiledSelection =   { 0, 117, 44, 255 },
   .optionText =           { 50, 50, 50, 255 },
   .optionBackground =     { 75, 75, 75, 255 },
   .optionHover =          { 175, 175, 175, 255 },
  };

  // @Nord theme
  static ImUITheme DK_ImUINordTheme = {
   .background =           { 46, 52, 64, 255 },
   .text =                 { 229, 233, 240, 255 },
   .button =               { 60, 56, 64, 255 },
   .buttonHover =          { 75, 71, 79, 255 },
   .buttonActive =         { 75, 71, 79, 255 },
   .toggle =               { 60, 56, 64, 255 },
   .toggleHover =          { 75, 71, 79, 255 },
   .toggleCursor =         { 175, 175, 175, 255 },
   .select =               { 60, 56, 64, 255 },
   .selectActive =         { 75, 71, 79, 255 },
   .slider =               { 60, 56, 64, 255 },
   .sliderCursor =         { 175, 175, 175, 255 },
   .sliderCursorHover =    { 175, 175, 175, 255 },
   .sliderCursorActive =   { 175, 175, 175, 255 },
   .property =             { 60, 56, 64, 255 },
   .border =               { 75, 71, 79, 255 },
   .textFiledCursor =      { 0, 228, 48, 255 },
   .textFiledSelection =   { 0, 117, 44, 255 },
   .optionText =           { 60, 56, 64, 255 },
   .optionBackground =     { 75, 71, 79, 255 },
   .optionHover =          { 175, 175, 175, 255 },
  };

  // @White theme
  static ImUITheme DK_ImUIWhiteTheme = {
   .background =           { 255, 255, 255, 255 },
   .text =                 { 50, 50, 50, 255 },
   .button =               { 200, 200, 200, 255 },
   .buttonHover =          { 175, 175, 175, 255 },
   .buttonActive =         { 175, 175, 175, 255 },
   .toggle =               { 200, 200, 200, 255 },
   .toggleHover =          { 175, 175, 175, 255 },
   .toggleCursor =         { 50, 50, 50, 255 },
   .select =               { 200, 200, 200, 255 },
   .selectActive =         { 175, 175, 175, 255 },
   .slider =               { 200, 200, 200, 255 },
   .sliderCursor =         { 50, 50, 50, 255 },
   .sliderCursorHover =    { 50, 50, 50, 255 },
   .sliderCursorActive =   { 50, 50, 50, 255 },
   .property =             { 200, 200, 200, 255 },
   .border =               { 175, 175, 175, 255 },
   .textFiledCursor =      { 0, 228, 48, 255 },
   .textFiledSelection =   { 0, 117, 44, 255 },
   .optionText =           { 200, 200, 200, 255 },
   .optionBackground =     { 175, 175, 175, 255 },
   .optionHover =          { 50, 50, 50, 255 },
  };

  //
  // @API function declarations
  //
  void DK_DrawColorPicker(ImUI* io, Vector2 pos, Color* result, bool* is_open);
  void DK_DrawSlider(ImUI* io, Vector2 position, float width, float height, float* value, float min, float max, float step, bool* focused);
  int DK_DrawButton(ImUI* io, Vector2 position, float width, float height, const char* text);
  int DK_DrawDropdown(ImUI* io, Vector2 position, float width, float height, const char* text, char** options, size_t el_size, int* selected, bool* is_open);
  const char* DK_DrawInputField(ImUI* io, Vector2 position, float width, float height, char* text, bool* focused, void (*callback)(const char*));

#if defined(DK_UI_IMPLEMENTATION)

  void DK_DrawColorPicker(ImUI* io, Vector2 pos, Color* result, bool* is_open)
  {
    const Color borderColor = Fade(io->theme->border, 1.0);
    const Color bgColor = Fade(io->theme->background, 0.5);
    const Color textColor = Fade(io->theme->text, 1.0);

    Color* color = result;
    static Vector2 mousePos = { 0, 0 };

    int offset = 30;

    Rectangle toggleButtonRect = { pos.x, pos.y, 20, 20 };

    Rectangle selectionRect = { pos.x + offset, pos.y + offset, 200, 200 };
    Rectangle hueRect = { pos.x + 210 + offset, pos.y + offset, 30, 200 };
    Rectangle alphaRect = { pos.x + 250 + offset, pos.y + offset, 30, 200 };

    Rectangle background = { pos.x + offset, pos.y + offset, 400, 200 };

    mousePos = GetMousePosition();

    DrawRectangle(toggleButtonRect.x,
                  toggleButtonRect.y,
                  toggleButtonRect.width,
                  toggleButtonRect.height,
                  *color);
    DrawRectangleLines(pos.x, pos.y, 20, 20, BLACK);

    if (CheckCollisionPointRec(mousePos, toggleButtonRect)) {
      char* text = "Toggle Color Picker";
      DrawText(text, pos.x + 30, pos.y + 5, 10, textColor);
    }

    // check if the color picker is open
    if (CheckCollisionPointRec(mousePos, toggleButtonRect)) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *is_open = !*is_open;
      }
    }

    if (*is_open) {
      if (CheckCollisionPointRec(mousePos, selectionRect)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
          color->r = (unsigned char)(255 * (mousePos.x - selectionRect.x) /
                                     selectionRect.width);
          color->g = (unsigned char)(255 * (1 - (mousePos.y - selectionRect.y) /
                                                  selectionRect.height));
        }
      } else if (CheckCollisionPointRec(mousePos, hueRect)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
          color->b = (unsigned char)(255 * (1 - (mousePos.y - hueRect.y) /
                                                  hueRect.height));
        }
      } else if (CheckCollisionPointRec(mousePos, alphaRect)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
          color->a = (unsigned char)(255 * (1 - (mousePos.y - alphaRect.y) /
                                                  alphaRect.height));
        }
      }

      DrawRectangleRounded(background, 0.1, 10, bgColor);

      // Color selection
      DrawRectangleGradientEx(selectionRect, GREEN, BLUE, RED, YELLOW);
      DrawRectangleRoundedLines(selectionRect, 0.1, 10, 4.0, borderColor);

      // Hue bar
      DrawRectangleGradientV(hueRect.x,
                             hueRect.y,
                             hueRect.width,
                             hueRect.height,
                             Fade(BLUE, 0.0),
                             Fade(BLUE, 1.0));
      DrawRectangleRoundedLines(hueRect, 0.1, 10, 4.0, borderColor);

      // Alpha bar
      DrawRectangleGradientV(alphaRect.x,
                             alphaRect.y,
                             alphaRect.width,
                             alphaRect.height,
                             Fade(WHITE, 0.0),
                             Fade(LIGHTGRAY, 1.0));
      DrawRectangleRoundedLines(alphaRect, 0.1, 10, 4.0, borderColor);

      // Cursor for color selection
      Vector2 markerPos = {
        pos.x + (color->r / 255.0f) * selectionRect.width + offset,
        pos.y + (1 - (color->g / 255.0f)) * selectionRect.height + offset
      };
      DrawCircleV(markerPos, 10, WHITE);
      DrawCircleSectorLines(markerPos, 10, 0, 360, 64, Fade(WHITE, 0.5));

      // Cursor for hue selection
      markerPos =
        (Vector2){ pos.x + 210 + hueRect.width / 2 + offset,
                   pos.y + (1 - (color->b / 255.0f)) * hueRect.height +
                     offset };
      DrawCircleV(markerPos, 10, WHITE);
      DrawCircleSectorLines(markerPos, 10, 0, 360, 64, Fade(WHITE, 0.5));

      // Cursor for alpha selection
      markerPos =
        (Vector2){ pos.x + 250 + alphaRect.width / 2 + offset,
                   pos.y + (1 - (color->a / 255.0f)) * alphaRect.height +
                     offset };
      DrawCircleV(markerPos, 10, WHITE);
      DrawCircleSectorLines(markerPos, 10, 0, 360, 64, Fade(GRAY, 0.7));

      // Color preview rectangle rounded
      DrawRectangleRoundedLines(
        (Rectangle){ pos.x + 300 + offset, pos.y + offset, 80, 80 },
        0.1,
        10,
        4.0,
        borderColor);
      DrawRectangleRounded(
        (Rectangle){ pos.x + 300 + offset, pos.y + offset, 80, 80 },
        0.1,
        10,
        *color);

      DrawRectangle(
        pos.x + 300 + offset, pos.y + 90 + offset, 80, 20, Fade(WHITE, 0.3));
      DrawRectangle(
        pos.x + 300 + offset, pos.y + 110 + offset, 80, 20, Fade(WHITE, 0.3));
      DrawRectangle(
        pos.x + 300 + offset, pos.y + 130 + offset, 80, 20, Fade(WHITE, 0.3));
      DrawRectangle(
        pos.x + 300 + offset, pos.y + 150 + offset, 80, 20, Fade(WHITE, 0.3));
      DrawRectangle(
        pos.x + 300 + offset, pos.y + 170 + offset, 80, 20, Fade(WHITE, 0.3));

      char text[32] = { 0 };
      sprintf(text, "%i", color->r);
      DrawText(text,
               pos.x + 300 + offset + 40 - MeasureText(text, 20) / 2,
               pos.y + 90 + offset + 11,
               20,
               textColor);
      sprintf(text, "%i", color->g);
      DrawText(text,
               pos.x + 300 + offset + 40 - MeasureText(text, 20) / 2,
               pos.y + 110 + offset + 11,
               20,
               textColor);
      sprintf(text, "%i", color->b);
      DrawText(text,
               pos.x + 300 + offset + 40 - MeasureText(text, 20) / 2,
               pos.y + 130 + offset + 11,
               20,
               textColor);
      sprintf(text, "%i", color->a);
      DrawText(text,
               pos.x + 300 + offset + 40 - MeasureText(text, 20) / 2,
               pos.y + 150 + offset + 11,
               20,
               textColor);
    }
  }

  void DK_DrawSlider(ImUI* io,
                     Vector2 position,
                     float width,
                     float height,
                     float* value,
                     float min,
                     float max,
                     float step,
                     bool* focused)
  {
    Color bgColor = Fade(io->theme->background, 0.2);
    Color borderColor = Fade(io->theme->border, 0.5);
    Color sliderColor = Fade(io->theme->slider, 0.8);
    Color sliderColorHover = Fade(io->theme->sliderCursorHover, 0.9);

    Rectangle slider = { position.x,
                         position.y + height,
                         width * (*value - min) / (max - min),
                         height };
    Rectangle sliderBounds = { position.x, position.y + height, width, height };

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), sliderBounds)) {
      *focused = true;
    } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      *focused = false;
    }

    DrawRectangleRoundedLines(sliderBounds, 0.5f, 1, 2, borderColor); // outline

    DrawRectangleRounded(sliderBounds, 0.5f, 10, bgColor); // bg
    if (CheckCollisionPointRec(GetMousePosition(), sliderBounds) || *focused) {
      DrawRectangleRounded(sliderBounds, 0.5f, 10, bgColor); // bg
    }

    DrawRectangleRounded(slider, 0.5f, 10, sliderColor); // slider
    if (CheckCollisionPointRec(GetMousePosition(), sliderBounds) || *focused) {
      DrawRectangleRounded(slider, 0.5f, 10, sliderColorHover);
    }

    if (step) {
      float stepCount = (max - min) / step;
      float stepWidth = width / stepCount;
      for (int i = 0; i < stepCount; ++i) {
        DrawRectangleLinesEx((Rectangle){ position.x + stepWidth * i,
                                          position.y + height,
                                          stepWidth,
                                          height },
                             1,
                             Fade(borderColor, 0.5f));
      }
    }

    if (*focused) {
      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        *value = min + (max - min) * (mouse.x - position.x) / width;
        if (step > 0)
          *value = roundf(*value / step) * step;
      }
    }

    if (*value < min)
      *value = min;
    if (*value > max)
      *value = max;
  }

  int DK_DrawButton(ImUI* io,
                    Vector2 position,
                    float width,
                    float height,
                    const char* text)
  {
    Color bgColor = Fade(io->theme->background, 0.2);
    Color borderColor = Fade(io->theme->border, 0.5);
    Color textColor = Fade(io->theme->text, 0.8);
    Color hoverColor = Fade(io->theme->buttonHover, 0.8);

    Rectangle buttonBounds = { position.x, position.y, width, height };

    DrawRectangleRoundedLines(buttonBounds, 0.5f, 1, 2, borderColor); // outline

    DrawRectangleRounded(buttonBounds, 0.5f, 10, bgColor); // bg
    if (CheckCollisionPointRec(GetMousePosition(), buttonBounds)) {
      DrawRectangleRounded(buttonBounds, 0.5f, 10, hoverColor); // bg
    }

    DrawTextEx(*io->font, text, position, height, 1, textColor);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (CheckCollisionPointRec(GetMousePosition(), buttonBounds)) {
        return 1;
      }
    }

    return 0;
  }

  int DK_DrawDropdown(ImUI* io,
                      Vector2 position,
                      float width,
                      float height,
                      const char* text,
                      char** options,
                      size_t el_size,
                      int* selected,
                      bool* is_open)
  {
    Color bgColor = Fade(io->theme->background, 0.2);
    Color borderColor = Fade(io->theme->border, 0.5);
    Color textColor = Fade(io->theme->text, 0.8);
    Color hoverColor = Fade(io->theme->buttonHover, 0.8);

    Color optionTextColor = Fade(io->theme->optionText, 0.8);
    Color optionHoverColor = Fade(io->theme->optionHover, 0.8);
    Color optionbgColor = Fade(io->theme->optionBackground, 0.8);

    Rectangle buttonBounds = { position.x, position.y, width, height };

    DrawRectangleRoundedLines(buttonBounds, 0.5f, 1, 2, borderColor); // outline

    DrawRectangleRounded(buttonBounds, 0.5f, 10, bgColor); // bg
    if (CheckCollisionPointRec(GetMousePosition(), buttonBounds)) {
      DrawRectangleRounded(buttonBounds, 0.5f, 10, hoverColor); // bg
    }

    DrawTextEx(
      *io->font,
      text,
      (Vector2){ position.x + 10, position.y + height / 2 - height / 2 },
      height,
      0,
      textColor);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (CheckCollisionPointRec(GetMousePosition(), buttonBounds)) {
        *is_open = !*is_open;
      }
    }

    if (*is_open) {
      for (int i = 0; i < el_size; i++) {
        int offset = i + 1;
        Rectangle optionBounds = {
          position.x, position.y + height * offset, width, height
        };

        DrawRectangle(optionBounds.x,
                      optionBounds.y,
                      optionBounds.width,
                      optionBounds.height,
                      optionbgColor);
        if (CheckCollisionPointRec(GetMousePosition(), optionBounds)) {
          DrawRectangle(optionBounds.x,
                        optionBounds.y,
                        optionBounds.width,
                        optionBounds.height,
                        optionHoverColor);
        }

        DrawTextEx(
          *io->font,
          options[i],
          (Vector2){ position.x + 10,
                     position.y + height * (i + 1) + height / 2 - height / 2 },
          height,
          1,
          optionTextColor);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
          if (CheckCollisionPointRec(GetMousePosition(), optionBounds)) {
            *is_open = !*is_open;
            *selected = i;
            return 1;
          }
        }
      }
    }

    return 0;
  }

  const char* DK_DrawInputField(ImUI* io,
                                Vector2 position,
                                float width,
                                float height,
                                char* text,
                                bool* focused,
                                void (*callback)(const char*))
  {
    // @Color definitions from theme
    Color bgColor = Fade(io->theme->background, 0.2);
    Color borderColor = Fade(io->theme->border, 0.5);
    Color textColor = Fade(io->theme->text, 0.8);
    Color activeColor = Fade(io->theme->buttonActive, 0.8);
    Color cursorColor = Fade(io->theme->textFiledCursor, 0.8);
    Color selectionColor = Fade(io->theme->textFiledSelection, 0.2);

    // @Clickable area for @Focus
    Rectangle buttonBounds = { position.x, position.y, width, height };

    int cursorPosEnd = 0;
    static int framesCounter = 0;
    static int cursorOffset = 0;
    static int cursorPos = 0;

    // @Focus on @Click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (CheckCollisionPointRec(GetMousePosition(), buttonBounds)) {
        *focused = true;
      } else {
        *focused = false;
      }
    }

    // @Border and @Background
    DrawRectangleRoundedLines(buttonBounds, io->style->roundness, 1, io->style->borderSize, borderColor);
    DrawRectangleRounded(buttonBounds, io->style->roundness, 10, bgColor);

    if (*focused) {
      ++framesCounter;

      // @Background for text input
      DrawRectangleRounded(buttonBounds, io->style->roundness, 10, activeColor);

      // @Selection rectangle (highlighted text)
      Rectangle selectionReactangle = { position.x + 8, position.y + 2.5,
                                        MeasureTextEx(*io->font, text, height, 1).x,
                                        height - 5 };
      DrawRectangleRec(selectionReactangle, selectionColor);

      int key = GetCharPressed();
      if ((key >= 32) && (key <= 125)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
          if (key >= 97 && key <= 122)
            key -= 32;
          else if (key >= 48 && key <= 57) {
            switch (key) {
              case 48:
                key = 41;
                break;
              case 49:
                key = 33;
                break;
              case 50:
                key = 64;
                break;
              case 51:
                key = 35;
                break;
              case 52:
                key = 36;
                break;
              case 53:
                key = 37;
                break;
              case 54:
                key = 94;
                break;
              case 55:
                key = 38;
                break;
              case 56:
                key = 42;
                break;
              case 57:
                key = 40;
                break;
            }
          } else {
            switch (key) {
              case 59:
                key = 58;
                break;
              case 61:
                key = 43;
                break;
              case 44:
                key = 60;
                break;
              case 45:
                key = 95;
                break;
              case 46:
                key = 62;
                break;
              case 47:
                key = 63;
                break;
              case 91:
                key = 123;
                break;
              case 92:
                key = 124;
                break;
              case 93:
                key = 125;
                break;
              case 39:
                key = 34;
                break;
              case 96:
                key = 126;
                break;
            }
          }
        }

        char str[2] = { 0 };
        str[0] = (char)key;

        memmove(&text[cursorPos + 1], &text[cursorPos], strlen(text) - cursorPos + 1);
        text[cursorPos] = str[0];

        cursorPos++;
      }

      // @Cursor movement (left arrow)
      if (IsKeyPressed(KEY_LEFT)) {
        if (cursorPos > 0) --cursorPos;
      }

      // @Cursor movement (right arrow)
      if (IsKeyPressed(KEY_RIGHT)) {
        if (cursorPos < strlen(text)) ++cursorPos;
      }

      char temp[1024];
      memcpy(temp, text, sizeof(temp));
      temp[cursorPos] = '\0';
      cursorPosEnd = MeasureTextEx(*io->font, temp, height, 1).x + cursorOffset;

      // @Delete
      if (IsKeyPressed(KEY_BACKSPACE)) {
        int len = strlen(text);
        if (len > 0) {
          if (cursorPos != 0) {
            for (int i = cursorPos; i < len; i++) {
              text[i - 1] = text[i];
            }
            text[len - 1] = '\0';
            cursorPos--;
          }
        }
      }

      // @Delete (key repeat on backspce)
      if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_BACKSPACE)) {
        if (framesCounter / 20 % 2) {
          int len = strlen(text);
          if (len > 0) {
            if (cursorPos != 0) {
              for (int i = cursorPos; i < len; i++) {
                text[i - 1] = text[i];
              }
              text[len - 1] = '\0';
              cursorPos--;
            }
          }
        }
      }

      // @Copy (CTRL+C)
      if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        SetClipboardText(text);
      }

      // @Paste (CTRL+V)
      if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V)) {
        strcat(text, GetClipboardText());
      }

      // @Submit (Enter)
      if (IsKeyPressed(KEY_ENTER)) {
        if (callback != NULL) { (*callback)(text); }
        cursorPos = 0;
      }
    }

    // @Text buffer drawing
    Vector2 textPos = { position.x + 5, position.y + height / 2 - height / 2 };
    DrawTextEx(*io->font,text, textPos, height, 1, textColor);

    if (strlen(text) != 0) { cursorOffset = 8; }
    else { cursorOffset = 5; }

    // @Cursor drawing (blinking animation every 20 frames)
    if (framesCounter / 20 % 2) {
      Rectangle cursorRec = { position.x + cursorPosEnd, position.y + 2.5, 10, height - 5 };
      DrawRectangleRec(cursorRec, cursorColor);
    }

    return text;
  }

#endif

#if defined(__cplusplus)
}
#endif

#endif // DK_UI_H
