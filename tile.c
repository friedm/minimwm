#include "tile.h"

//set focus to the current screen's desktop's current window
void updatefocus(void) {
   struct window *currentwin = desktops[screens[currentscreen].desktop].current;
   if (currentwin != NULL) {
      XRaiseWindow(display,currentwin->window);//only matters if we're not tiling
      XSetInputFocus(display,currentwin->window,RevertToPointerRoot,CurrentTime);
   }
   XSync(display,False);
}

void focusnextwindow(void) {
   switchnextwindow();
   updatefocus();
}

void focusprevwindow(void) {
   switchprevwindow();
   updatefocus();
}
