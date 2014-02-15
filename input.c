#include "input.h"

const char *keystrs[] = {
   "MS-q",     //key 0 
   "MS-Return", //key 1
   "S-c"     //key 2
};

void initkeys(void) {
   numkeys = sizeof(keystrs)/sizeof(keystrs[0]);
   keycodes = malloc(numkeys * sizeof(struct key));

   int i;
   for (i=0; i<numkeys; i++) {
      keycodes[i].code = getkeycodefromstring(keystrs[i]);
      keycodes[i].mask = getmaskstr(keystrs[i]); 
   }
}

void freekeys(void) {
   free(keycodes);
}

void grabkeys(void) {
   XUngrabKey(display, AnyKey, AnyModifier, root);
   int i;
   for (i=0; i<numkeys; i++) {
      XGrabKey(display, keycodes[i].code, keycodes[i].mask, root, True, GrabModeAsync, GrabModeAsync);
   }
}

int handlekey(int code, int mask) {
   int key = findregisteredkey(code,mask);
   if (key == -1) return 0;

   switch(key) {
      case 0: return 1; break;
      case 1: 
              return spawn("/usr/bin/urxvt"); 
              break;
      case 2: l("WHEEEE"); break;
   }
}

//could.... sort key codes and do a binary search, but really unnecessary
int findregisteredkey(int code, int mask) {
   int i;
   for (i=0; i<numkeys; i++) {
      if (keycodes[i].code == code && keycodes[i].mask == mask) {
         return i;
      }
   }
   return -1;
}
