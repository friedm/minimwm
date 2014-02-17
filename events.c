#include <X11/Xlib.h>

#include "thewm.h"
#include "input.h"
#include "tile.h"

/*
 * All X event handlers
 */

int keypress(XEvent *ev) {
   return handlekey(ev->xkey.keycode, ev->xkey.state); 
}

//a window has requested that X map a window
//X passes this here
int maprequest(XEvent *ev) {
   Window win = ev->xmaprequest.window;
   XWindowAttributes winattr;

   char *name;
   XFetchName(display,win,&name);
   lf("Got map request! %X : %s",win, name);
   if (XGetWindowAttributes(display, win, &winattr) && winattr.override_redirect) {
      l("Window requested override redirect");
      //TODO more here?
      return 0;
   }

   XSelectInput(display, win, PropertyChangeMask|FocusChangeMask);
   XMapWindow(display, win);


   //update data structures:add new window
   addwindowdesktop(win);
   logcurrentdesktop();

   //tile
   tile();
   updatefocus();
   
   return 0;
}

int mapnotify(XEvent *ev) {
   //lf("Got map notify! %X",ev->xmap.window);
   return 0;
}

int unmapnotify(XEvent *ev) {
   //lf("Got unmap notify! %X",ev->xunmap.window);
   return 0; 
}

int destroynotify(XEvent *ev) {
   lf("Got destroy notify! %X",ev->xdestroywindow.window);

   //update data structures:remove window
   removewindow(ev->xdestroywindow.window);
   logcurrentdesktop();

   tile();
   updatefocus();//set focus to the active window

   return 0;
}

int configurerequest(XEvent *ev) {
   l("GOT CONFIGURE REQUEST");
}

int handleevent(XEvent *ev) {
   switch(ev->type) {
      case KeyPress: return keypress(ev); break;
      case MapRequest: return maprequest(ev); break;
      case MapNotify: return mapnotify(ev); break;
      case UnmapNotify: return unmapnotify(ev); break;
      case DestroyNotify: return destroynotify(ev); break;
      case ConfigureRequest: return configurerequest(ev); break;
   }
   return 0;
}
