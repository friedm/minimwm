#include "actions.h"
#include "screen.h"

int a_quit(void) {
   return 1;
}

int a_spawnterm(void) {
   return spawn("/usr/bin/urxvt");
}

int a_toggletilealg(void) {
   toggletilealg();
   tile();
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
   tile();
   return 0;
}

int a_moveprev(void) {
   movewindowprev();
   tile();
   return 0;
}

int a_lesswidth(void) {
   changecurrentwindowwidth(-20); 
   tile();
   return 0;
}

int a_morewidth(void) {
   changecurrentwindowwidth(20);
   tile();
   return 0;
}

int a_resetwidth(void) {
   resetcurrentwindowwidths();
   tile();
   return 0;
}

int a_changedesk1(void) { changedesktop(0); return 0; }
int a_changedesk2(void) { changedesktop(1); return 0; }
int a_changedesk3(void) { changedesktop(2); return 0; }
int a_changedesk4(void) { changedesktop(3); return 0; }
int a_changedesk5(void) { changedesktop(4); return 0; }
int a_changedesk6(void) { changedesktop(5); return 0; }
int a_changedesk7(void) { changedesktop(6); return 0; }
int a_changedesk8(void) { changedesktop(7); return 0; }
int a_changedesk9(void) { changedesktop(8); return 0; }
int a_changedesk0(void) { changedesktop(9); return 0; }

int a_movedesk1(void) { movecurrenttodesktop(0); return 0; }
int a_movedesk2(void) { movecurrenttodesktop(1); return 0; }
int a_movedesk3(void) { movecurrenttodesktop(2); return 0; }
int a_movedesk4(void) { movecurrenttodesktop(3); return 0; }
int a_movedesk5(void) { movecurrenttodesktop(4); return 0; }
int a_movedesk6(void) { movecurrenttodesktop(5); return 0; }
int a_movedesk7(void) { movecurrenttodesktop(6); return 0; }
int a_movedesk8(void) { movecurrenttodesktop(7); return 0; }
int a_movedesk9(void) { movecurrenttodesktop(8); return 0; }
int a_movedesk0(void) { movecurrenttodesktop(9); return 0; }
