#include <string.h>

#include "utils.h"

/*
 * Parse strings, deal with key codes, etc...
 */

KeyCode getKCode(KeySym k) {
   return XKeysymToKeycode(display, k);
}

KeyCode getKCodeStr(const char *kstr) { 
   return getKCode(XStringToKeysym(kstr));
}

//get the mask code from string form
//supports shift and mod1 for now
int getmaskstr(char *kstr) {
   char * line = strdup(kstr); 
   char *maskstr = strtok(line,"-"); 
   char *keystr = strtok(NULL,"-");
   if (!keystr) //no mask
      return 0;//no kb state

   if (strchr(maskstr,'S') && strchr(maskstr,'M'))
      return Mod1Mask|ShiftMask; 
   else if (strchr(maskstr,'S')) return ShiftMask;
   else if (strchr(maskstr,'M')) return Mod1Mask; 
   else return 0;//bad mask string
}

int getkeycodefromstring(const char *kstr) {
   char * line = strdup(kstr);
   char *maskstr = strtok(line,"-");
   char *keystr = strtok(NULL,"-");

   if (!keystr) {//no mask, maskstr is keystr
      keystr = maskstr;
   }
   return getKCodeStr(keystr);
}

//spawn a new process and run a command
int spawn(const char *cmd) {
   int pid = fork();
   if (pid < 0) l("error spawning process");
   else if (pid == 0) {
      setsid();
      const char *args[] = {cmd, NULL};
      execvp(cmd, args);
      return 1;
   }
   else {
      return 0;
   }
}

void kill(Window window) {
   l("killing");
   Atom *prot = NULL;
   int n = -1;
   if (XGetWMProtocols(display, window, &prot, &n)) {
      l("got prots");
      while (--n >= 0 && prot[n] != XInternAtom(display, "WM_DELETE_WINDOW", False));
   }
   l("HERE");
   if (n < 0) {
      l("hard kill");
      XKillClient(display, window);
   }
   else {
      l("soft kill");
      XEvent ev;
      ev.type = ClientMessage;
      ev.xclient.window = window;
      ev.xclient.format = 32;
      ev.xclient.message_type = XInternAtom(display, "WM_PROTOCOLS", False);
      ev.xclient.data.l[0] = XInternAtom(display, "WM_DELETE_WINDOW", False);
      ev.xclient.data.l[1] = CurrentTime;
      XSendEvent(display, window, False, NoEventMask, &ev);
   }
   if (prot) XFree(prot);
}
