#pragma once

#define T_CLEAR printf("\x1b[?25l\x1b[H\x1b[J") // hide cursor, move it to HOME and delete right of cousor pos
#define TC_END printf("\x1b[?25h")              // show cursor

// To Enter Game
void StartWindow(const char **_optionv); // Setting Window
void SetWindowSize(int width, int height);
void setFontAttributes(int style, int foreground, int background);