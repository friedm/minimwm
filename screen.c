#include "screen.h"

void initscreens(void) {
   numscreens = ScreenCount(display);
   screens = malloc(numscreens * sizeof(struct screen));
   int i;
   for (i=0; i<numscreens; i++) {
      screens[i].screen = ScreenOfDisplay(display,i);
      screens[i].desktop = i;//initially screens are parallel to desktops
      screens[i].width = screens[i].screen->width;
      screens[i].height = screens[i].screen->height;
   }
}

void freescreens(void) {
   free(screens);
}
