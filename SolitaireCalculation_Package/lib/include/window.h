#pragma once

#define T_CLEAR printf("\x1b[?25l\x1b[H\x1b[J") // hide cursor, move it to HOME and delete right of cousor pos
#define TR_CLEAR printf("\033[K")               //
#define TC_END printf("\x1b[?25h")              // show cursor
#define UP_CURSOR printf("\033[A")              // set cursor above currently line
#define DOWN_CURSOR printf("\033[D")            // set cursor below currently line

// To Enter Game
void StartWindow(const char **_optionv); // Setting Window
void SetWindowSize(int width, int height);
void setFontAttributes(int style, int foreground, int background);