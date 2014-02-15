#include <X11/Xlib.h>

#include "thewm.h"
#include "input.h"

int keypress(XEvent *ev) {
   return handlekey(ev->xkey.keycode, ev->xkey.state); 
}

//a window has requested that X map a window
//X passes this here
int maprequest(XEvent *ev) {
   Window win = ev->xmaprequest.window;
   XWindowAttributes winattr;

   if (XGetWindowAttributes(display, win, &winattr) && winattr.override_redirect) {
      //TODO more here?
      return 0;
   }

   XSelectInput(display, win, PropertyChangeMask|FocusChangeMask);
   XMapWindow(display, win);

   XMoveResizeWindow(display, win, 0,0,1920, 1080);

   XSetInputFocus(display,win,RevertToPointerRoot,CurrentTime);
   XSync(display,False);

   //TODO tile, update focus, etc.
   return 0;
}

int unmapnotify(XEvent *ev) {
   //update data structures
   return 0; 
}

int destroynotify(XEvent *ev) {
   //update data structures
   return 0;
}

int handleevent(XEvent *ev) {
   switch(ev->type) {
      case KeyPress: return keypress(ev); break;
      case MapRequest: return maprequest(ev); break;
      case UnmapNotify: return unmapnotify(ev); break;
      case DestroyNotify: return destroynotify(ev); break;
   }
   return 0;
}
