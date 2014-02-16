#include "actions.h"

int a_quit(void) {
   return 1;
}

int a_spawnterm(void) {
   return spawn("/usr/bin/urxvt");
}

int a_focusnext(void) {
   focusnextwindow();
   return 0;
}

int a_focusprev(void) {
   focusprevwindow();
   return 0;
}

int a_movenext(void) {
   movewindownext();
}

int a_moveprev(void) {
   movewindowprev();
}
