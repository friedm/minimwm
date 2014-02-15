#include <X11/Xlib.h>
#include <stdlib.h>

#include "thewm.h"

struct key {
   int code;
   int mask;
};
struct key *keycodes;

int numkeys;

void initkeys(void);
void freekeys(void);
void grabkeys(void);
int handlekey(int,int);

int findregisteredkey(int,int);
