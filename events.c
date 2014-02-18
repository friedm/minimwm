#include <X11/Xlib.h>

#include "thewm.h"
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

void mapnotify(XEvent *ev) {
   lf("Got map notify! %X",ev->xmap.window);
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

void configurerequest(XEvent *ev) {
   //lf("GOT CONFIGURE REQUEST: %X",ev->xconfigurerequest.window);
   //lf("x: %d, y: %d, width: %d, height: %d",ev->xconfigurerequest.x,ev->xconfigurerequest.y, ev->xconfigurerequest.width, ev->xconfigurerequest.height);
   ////configure window how it wants, then tile over it
   //XConfigureRequestEvent *cr = &ev->xconfigurerequest;
   //XWindowChanges wc = { cr->x, cr->y, cr->width, cr->height, cr->border_width, cr->above, cr->detail };
   //if (XConfigureWindow(display, cr->window, cr->value_mask, &wc)) XSync(display, False);
   //tile();
   //updatefocus();
}

void handleevent(XEvent *ev) {
   switch(ev->type) {
      case KeyPress: keypress(ev); break;
      case MapRequest: maprequest(ev); break;
      case MapNotify: mapnotify(ev); break;
      case UnmapNotify: unmapnotify(ev); break;
      case DestroyNotify: destroynotify(ev); break;
      case ConfigureRequest: configurerequest(ev); break;
   }
}
