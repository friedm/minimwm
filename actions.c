#include "actions.h"
#include "screen.h"

void a_quit(void) {
   running = 0;
}

void a_spawnterm(void) {
   spawn("/usr/bin/urxvt");
}

void a_killcurrent(void) {
   killcurrent();
}

void a_toggletilealg(void) {
   toggletilealg();
   tile();
}

void a_focusnext(void) {
   focusnextwindow();
}

void a_focusprev(void) {
   focusprevwindow();
}

void a_movenext(void) {
   movewindownext();
   tile();
}

void a_moveprev(void) {
   movewindowprev();
   tile();
}

void a_lesswidth(void) {
   changecurrentwindowwidth(-20); 
   tile();
}

void a_morewidth(void) {
   changecurrentwindowwidth(20);
   tile();
}

void a_resetwidth(void) {
   resetcurrentwindowwidths();
   tile();
}

void a_changedesk1(void) { changedesktop(0); }
void a_changedesk2(void) { changedesktop(1); }
void a_changedesk3(void) { changedesktop(2); }
void a_changedesk4(void) { changedesktop(3); }
void a_changedesk5(void) { changedesktop(4); }
void a_changedesk6(void) { changedesktop(5); }
void a_changedesk7(void) { changedesktop(6); }
void a_changedesk8(void) { changedesktop(7); }
void a_changedesk9(void) { changedesktop(8); }
void a_changedesk0(void) { changedesktop(9); }

void a_movedesk1(void) { movecurrenttodesktop(0); }
void a_movedesk2(void) { movecurrenttodesktop(1); }
void a_movedesk3(void) { movecurrenttodesktop(2); }
void a_movedesk4(void) { movecurrenttodesktop(3); }
void a_movedesk5(void) { movecurrenttodesktop(4); }
void a_movedesk6(void) { movecurrenttodesktop(5); }
void a_movedesk7(void) { movecurrenttodesktop(6); }
void a_movedesk8(void) { movecurrenttodesktop(7); }
void a_movedesk9(void) { movecurrenttodesktop(8); }
void a_movedesk0(void) { movecurrenttodesktop(9); }
