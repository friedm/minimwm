#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <X11/Xlib.h>

#include "minimwm.h"
#include "events.h"
#include "input.h"
#include "tile.h"

/*
 * minimwm - minimal tiling window manager
 * author: Matt Friedman
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
   initdesktops();
   initscreens();

   XSelectInput(display, root, SubstructureRedirectMask|ButtonPressMask|SubstructureNotifyMask|PropertyChangeMask);
   XSync(display, False);

   grabkeys();

   running = 1;
   XEvent ev;
   while (running) {
      XNextEvent(display, &ev);
      handleevent(&ev);
   }
   logcurrentdesktop();
   l("exiting...");

   XCloseDisplay(display);

   //free memory 
   freescreens();
   freedesktops();
   freekeys();

   closelog();
   
   return 0;
}
