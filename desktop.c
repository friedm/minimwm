#include "minimwm.h"
#include "desktop.h"
#include "screen.h"

void initdesktops(void) {
   int i;
   for (i=0; i<NUM_DESKTOPS; i++) {
      desktops[i].tilealg = 0;
      desktops[i].current = NULL;
      initll(&desktops[i].headwin, &desktops[i].tailwin);
   }
}

void freedesktops(void) {
   int i;
   for (i=0; i<NUM_DESKTOPS; i++) {
      freell(desktops[i].headwin, desktops[i].tailwin);
   }
}

void addwindowdesktop(Window w) {
   desktops[screens[currentscreen].desktop].current = addll(
         desktops[screens[currentscreen].desktop].headwin,
         w);
   adjustwidthsll(desktops[screens[currentscreen].desktop].headwin,screens[currentscreen].width);
}

void removecurrentwindowdesktop(void) { //the current one
  desktops[screens[currentscreen].desktop].current = removell(
         desktops[screens[currentscreen].desktop].current,
         desktops[screens[currentscreen].desktop].headwin);
  adjustwidthsll(desktops[screens[currentscreen].desktop].headwin,screens[currentscreen].width);
}

//traverse structure, find and remove specific window id
int removewindow(Window winid) {
   if (desktops[screens[currentscreen].desktop].current != NULL && 
         desktops[screens[currentscreen].desktop].current->window == winid) {

      removecurrentwindowdesktop();
      return 1;
   }

   int i;
   for (i=0; i<NUM_DESKTOPS; i++) {
      if (findremovell(winid,desktops[i].headwin)) {
         adjustwidthsll(desktops[screens[currentscreen].desktop].headwin,screens[currentscreen].width);
         return 1;//assuming the window ids are unique
      }
   }
   return 0;
}

int removewindowfromcurrentdesktop(Window winid) {
   if (desktops[screens[currentscreen].desktop].current != NULL &
         desktops[screens[currentscreen].desktop].current->window == winid) {
      removecurrentwindowdesktop();
      return 1;
   }
   if (findremovell(winid, desktops[screens[currentscreen].desktop].headwin)) {
      adjustwidthsll(desktops[screens[currentscreen].desktop].headwin,screens[currentscreen].width);
      return 1;
   }
   return 0;
}

int windowadded(Window window) {
   int i;
   for (i=0; i<NUM_DESKTOPS; i++) {
      struct window *trav;
      for (trav = desktops[i].headwin; trav->next->next != NULL; trav = trav->next) {
         if (trav->next->window == window) return 1;
      }
   }
   return 0;
}

void switchnextwindow(void) {
   struct desktop dt = desktops[screens[currentscreen].desktop]; 
   if (dt.current == NULL) return; //empty desktop, nothing to do
   desktops[screens[currentscreen].desktop].current = getnextll(dt.current, dt.headwin);
}

void switchprevwindow(void) {
   struct desktop dt = desktops[screens[currentscreen].desktop];
   if (dt.current == NULL) return; //empty desktop, nothing to do
   desktops[screens[currentscreen].desktop].current = getprevll(dt.current,dt.tailwin);
}

void movewindownext(void) {
   if (desktops[screens[currentscreen].desktop].current == NULL) return; //empty desktop, nothing to do   
   desktops[screens[currentscreen].desktop].current = swapnextll(
         desktops[screens[currentscreen].desktop].current,
         desktops[screens[currentscreen].desktop].headwin);
}

void movewindowprev(void) {
   if (desktops[screens[currentscreen].desktop].current == NULL) return; //empty desktop, nothing to do
   desktops[screens[currentscreen].desktop].current = swapprevll(
         desktops[screens[currentscreen].desktop].current,
         desktops[screens[currentscreen].desktop].tailwin);
}

void logcurrentdesktop(void) {
   logll(desktops[screens[currentscreen].desktop].headwin);
}
