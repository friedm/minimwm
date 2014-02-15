#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <X11/Xlib.h>

#include "thewm.h"
#include "events.h"
#include "input.h"

/*
 * Basic communication with X
 */

int main(void) {
   int screen = 0;

   initlog();

   //set up display
   if (!(display = XOpenDisplay(0x0))) {
      l("Display could not be opened");
      return 1;
   }
   root = RootWindow(display,screen);

   //allocate memory
   initkeys();

   XSelectInput(display, root, SubstructureRedirectMask|ButtonPressMask|SubstructureNotifyMask|PropertyChangeMask);
   XSync(display, False);

   grabkeys();

   XEvent ev;
   while (1) {
      XNextEvent(display, &ev);
      if (handleevent(&ev) == 1) break;
   }
   l("exiting...");

   XCloseDisplay(display);

   //free memory 
   freekeys();

   closelog();
   
   return 0;
}
