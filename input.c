#include "input.h"
#include "actions.h"

/*
 * Defines and handles key presses
 */

void *keystrs[][2] = {
   { "MS-q", &a_quit }, 
   { "MS-Return", &a_spawnterm },
   { "M-j", &a_focusprev },
   { "M-k", &a_focusnext },
   { "MS-j", &a_moveprev },
   { "MS-k", &a_movenext }
};

void initkeys(void) {
   numkeys = sizeof(keystrs)/sizeof(keystrs[0]);
   keycodes = malloc(numkeys * sizeof(struct key));

   int i;
   for (i=0; i<numkeys; i++) {
      keycodes[i].code = getkeycodefromstring(keystrs[i][0]);
      keycodes[i].mask = getmaskstr(keystrs[i][0]); 
      keycodes[i].action = keystrs[i][1];
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
   if (key == -1) return 0;//not a registered key

   return keycodes[key].action();
}

int findregisteredkey(int code, int mask) {
   int i;
   for (i=0; i<numkeys; i++) {
      if (keycodes[i].code == code && keycodes[i].mask == mask) {
         return i;
      }
   }
   return -1;
}
