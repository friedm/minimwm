#include <X11/Xlib.h>
#include <stdlib.h>

#include "minimwm.h"

/*
 * Window struct
 *    Operations: ll operations, applies to any window ll
 *                independent of current window or desktop
 */

struct window {
   Window window;//X window reference
   char ignore;//if true, this window isn't here
   int width;//possibly percentages of the screen, won't be used for every tiling algorithm
   //int height;
   struct window *next;
   struct window *prev; 
};

void initll (struct window **head, struct window **tail);
void freell (struct window *head, struct window *tail);
struct window *addll  (struct window *head, Window window);
struct window *removell (struct window *remove, struct window *head);
char findremovell(Window window,struct window *head);

struct window *getnextll (struct window *current, struct window *head);
struct window *getprevll (struct window *current, struct window *tail);

struct window *swapnextll(struct window *current, struct window *head);
struct window *swapprevll(struct window *current, struct window *tail);

void swapll(struct window *first, struct window *second);

int sizell(struct window *head);
void adjustwidthsll(struct window *head, int screenwidth);

void logll (struct window *head);
