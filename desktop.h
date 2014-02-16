#include "window.h"

/*
 * Desktop struct and array
 *    Operations: move window to a different desktop
 *                change current window (focus)
 *                move current window
 *                kill current window
 *                create new window to be current
 */
#define NUM_DESKTOPS 10//fixed, correspond to kb number keys

struct desktop {
   int tilealg;
   //TODO duplicate width/height fields?
   struct window *headwin;
   struct window *tailwin;
   struct window *current;
};

struct desktop desktops [NUM_DESKTOPS];//fixed number of desktops

void initdesktops(void);   //initialize window pointers
                           //set default tiling algorithm
void freedesktops(void);
                        
void movewindowtodesktop(int);

void switchnextwindow(void);
void switchprevwindow(void);

void movenextwindow(void);
void moveprevwindow(void);

void addwindowdesktop(Window);
void removecurrentwindowdesktop(void);
