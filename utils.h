#include <X11/Xlib.h>

#include "thewm.h"

KeyCode getKCode(KeySym);
KeyCode getKCodeStr(const char *);
int getmaskstr(char *);
int getkeycodefromstring(const char *);


int spawn(const char *);
void kill(Window window);
