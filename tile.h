#include <X11/Xlib.h>

#include "screen.h"
#include "desktop.h"

/*
 * Top-level code to manage the screen/desktop/window structure
 * Interacts with the data structure and X
 */

void updatefocus(void);

void focusnextwindow(void);
void focusprevwindow(void);

void changecurrentwindowwidth(int); 
void resetwindowwidths(void);

void unmapwindows(void);
void mapwindows(void);

void changedesktop(int);

void tile(void);
void toggletilealg(void);
