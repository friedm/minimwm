#include "thewm.h"
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
   ld(desktops[screens[currentscreen].desktop].current);
   desktops[screens[currentscreen].desktop].current = addll(
         desktops[screens[currentscreen].desktop].headwin,
         w);
}

void removecurrentwindowdesktop(void) { //the current one
  desktops[screens[currentscreen].desktop].current = removell(
         desktops[screens[currentscreen].desktop].current,
         desktops[screens[currentscreen].desktop].headwin);
}

//traverse structure, find and remove specific window id
void removewindow(Window winid) {
   if (desktops[screens[currentscreen].desktop].current != NULL && 
         desktops[screens[currentscreen].desktop].current->window == winid) {

      removecurrentwindowdesktop();
      return;
   }


   int i;
   for (i=0; i<NUM_DESKTOPS; i++) {
      if (findremovell(winid,desktops[i].headwin)) return;//assuming the window ids are unique
   }
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
   swapnextll(
         desktops[screens[currentscreen].desktop].current,
         desktops[screens[currentscreen].desktop].headwin);
}

void movewindowprev(void) {
   if (desktops[screens[currentscreen].desktop].current == NULL) return; //empty desktop, nothing to do
   swapprevll(
         desktops[screens[currentscreen].desktop].current,
         desktops[screens[currentscreen].desktop].tailwin);
}

void logcurrentdesktop(void) {
   logll(desktops[screens[currentscreen].desktop].headwin);
}
