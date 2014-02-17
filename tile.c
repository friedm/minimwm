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

void changecurrentwindowwidth(int change) {
   int count = sizell(desktops[screens[currentscreen].desktop].headwin);
   if (count == 0 || count == 1) return;
   int diff = (count-1) * change;
   struct window *trav = desktops[screens[currentscreen].desktop].headwin;
   while (trav->next->next != NULL) {
      if (trav->next == desktops[screens[currentscreen].desktop].current) trav->next->width += diff;
      else trav->next->width -= change;
      trav = trav->next;
   }
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

void movecurrenttodesktop(int desk) {
   int olddesk = screens[currentscreen].desktop;
   if (desktops[olddesk].current == NULL) return;//no current window, nothing to do
   unmapwindows();

   Window window = desktops[olddesk].current->window;
   removecurrentwindowdesktop();
   screens[currentscreen].desktop = desk;
   addwindowdesktop(window);
   screens[currentscreen].desktop = olddesk;

   mapwindows();
   tile();
   updatefocus();
}

void tilevertical(void) {//tile windows horizontally
   int width = screens[currentscreen].width;
   int height = screens[currentscreen].height;

   int pos = 0;

   //assume all width properties add to screen width
   struct window *trav = desktops[screens[currentscreen].desktop].headwin;
   while(trav->next->next != NULL) {
      XMoveResizeWindow(display, trav->next->window,pos,0,trav->next->width,height);
      pos += trav->next->width;
      trav = trav->next;
   }
}

void tilefullscreen(void) {//set all windows to full screen size
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
