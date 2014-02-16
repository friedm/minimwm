#include <X11/Xlib.h>
#include <stdlib.h>

#include "thewm.h"

/*
 * Screen struct and array
 *    Operations: change the current screen (focus) 
 *                switch the desktop of the current screen
 *                move the current window to another screen
 */

struct screen {
   int width;
   int height;
   //struct desktop *desktop;//or just the index?
   int desktop;
   Screen *screen;//X identifier
};

struct screen *screens; //dynamic array -- set based on current number of screens
int numscreens; //max 10
int currentscreen; //0

void initscreens(void);
   //call X, find number of screens
   //malloc screens
   //TODO configurable screen order
   //align to first n desktops
void freescreens(void);

void focusnextscreen(void);
void focusprevscreen(void);

void swapcurrentscreendesktop(int);//new desktop id to swap with

void movewindownextscreen(void);
void movewindowprevscreen(void);
