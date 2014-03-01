#include <X11/Xlib.h>

#include "minimwm.h"
#include "input.h"
#include "tile.h"

/*
 * All X event handlers
 */

void keypress(XEvent *ev) {
   handlekey(ev->xkey.keycode, ev->xkey.state); 
}

//a window has requested that X map a window
//X passes this here
void maprequest(XEvent *ev) {
   Window win = ev->xmaprequest.window;
   XWindowAttributes winattr;

   char *name;
   XFetchName(display,win,&name);
   lf("Got map request! %X : %s",win, name);
   if (XGetWindowAttributes(display, win, &winattr) && winattr.override_redirect) {
      l("Window requested override redirect");
      return;
   }

   XSelectInput(display, win, PropertyChangeMask|FocusChangeMask);
   XMapWindow(display, win);

   //update data structures:add new window
   addwindowdesktop(ev->xmap.window);
   logcurrentdesktop();

   //tile
   tile();
   updatefocus();
}

void unmapnotify(XEvent *ev) {
   lf("Got unmap notify! %X",ev->xunmap.window);
   //since we do tell windows to map and unmap, we can't remove all windows here
   //in order to remove ghost windows, only remove the window if its in the current desktop
   if (removewindow(ev->xunmap.window)) {
      logcurrentdesktop();
      tile();
      updatefocus(); 
   }
}

void destroynotify(XEvent *ev) {
   lf("Got destroy notify! %X",ev->xdestroywindow.window);

   //update data structures:remove window
   if (removewindow(ev->xdestroywindow.window)) {
      logcurrentdesktop();

      tile();
      updatefocus();//set focus to the active window
   }
}

void handleevent(XEvent *ev) {
   switch(ev->type) {
      case KeyPress: keypress(ev); break;
      case MapRequest: maprequest(ev); break;
      case UnmapNotify: unmapnotify(ev); break;
      case DestroyNotify: destroynotify(ev); break;
   }
}
