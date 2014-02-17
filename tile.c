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

void unmapwindows(void) {
   struct window *trav = desktops[screens[currentscreen].desktop].headwin;
   while (trav->next->next != NULL) {
      XUnmapWindow(display,trav->next->window);
      trav = trav->next;
   }
}

void mapwindows(void) {
   struct window *trav = desktops[screens[currentscreen].desktop].headwin;
   while (trav->next->next != NULL) {
      XMapWindow(display,trav->next->window);
      trav = trav->next;
   }
}

void changedesktop(int desk) {
   unmapwindows();
   screens[currentscreen].desktop = desk;
   mapwindows();
   tile();
   updatefocus();
}

void tilevertical(void) {//tile windows horizontally
   l("tilevert");
}

void tilefullscreen(void) {//set all windows to full screen size
   l("tilefull");
   struct window *trav = desktops[screens[currentscreen].desktop].headwin;
   while (trav->next->next != NULL) {
      XMoveResizeWindow(display, trav->next->window, 0,0,screens[currentscreen].width, screens[currentscreen].height);
      trav = trav->next;
   }
}

void tile(void) {
   switch(desktops[screens[currentscreen].desktop].tilealg) {
      case 0: tilevertical(); break;
      case 1: tilefullscreen(); break;
   }
}

void toggletilealg(void) {
   if (desktops[screens[currentscreen].desktop].tilealg == 0) 
      desktops[screens[currentscreen].desktop].tilealg = 1;
   else desktops[screens[currentscreen].desktop].tilealg = 0;
}
