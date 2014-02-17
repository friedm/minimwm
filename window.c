#include "window.h"

void initll (struct window **head, struct window **tail) {
   *head = malloc(sizeof(struct window));
   *tail = malloc(sizeof(struct window));
   (*head)->prev = NULL;
   (*head)->next = *tail;
   (*tail)->prev = *head;
   (*tail)->next = NULL;
}

void freell (struct window *head, struct window *tail) {
   //empty and free ll
   while (head->next->next != NULL) removell(head->next,head);
   free(head);
   free(tail);
}

struct window *addll(struct window *head, Window window){
   struct window * newwindow = malloc(sizeof(struct window));
   newwindow->ignore = 0;
   newwindow->window = window;
   newwindow->width = -1;//needs to be initialized

   newwindow->prev = head;
   newwindow->next = head->next;
   head->next = newwindow;
   newwindow->next->prev = newwindow;

   return newwindow;
}

struct window *removell(struct window *remove, struct window *head) {
   if (remove->next == NULL || remove->prev == NULL) {
      l("Tried to remove head or tail!");
      return;
   }

   remove->prev->next = remove->next;
   remove->next->prev = remove->prev;

   struct window *replacement;
   if (remove->prev->prev != NULL) //there is a previous node
      replacement = remove->prev;
   else if (remove->next->next != NULL) //there is a next node
      replacement = remove->next;
   else //the LL is now empty
      replacement = NULL;

   free(remove);

   return replacement;
}

char findremovell(Window window, struct window *head){
   struct window *trav = head;
   while(trav->next->next != NULL) {
      if (trav->next->window == window) {
         removell(trav->next,head);
         return 1;
      }
      trav = trav->next;
   }
   return 0;
}

struct window *getnextll(struct window *current, struct window *head){
   if (head->next->next == NULL) return NULL; //empty ll
   if (current->next->next != NULL) return current->next; //there is another element to the right
   else return head->next;
}

struct window *getprevll(struct window *current, struct window *tail){
   if (tail->prev->prev == NULL) return NULL; //empty ll
   if (current->prev->prev != NULL) return current->prev; //there is another element to the left
   else return tail->prev;
}

void swapnextll(struct window *current, struct window *head) {
   if (head->next->next == NULL) return; //empty ll   
   if (current->next->next != NULL) { //swap with it
      swapll(current,current->next);
   }
   else {//swap with the first node
      swapll(head->next,current);
   }
}

void swapprevll(struct window *current, struct window *tail) {
   if (tail->prev->prev == NULL) return; //empty ll
   if (current->prev->prev != NULL) { //swap   
      swapll(current->prev,current);
   }
   else {//swap with the last node
      swapll(current,tail->prev);
   }
}

void swapll(struct window *first, struct window *last) {
   //fake it
   Window temp = first->window;
   first->window = last->window;
   last->window = temp;
}

int sizell(struct window *head) {
   int count = 0;
   struct window *trav = head;
   while(trav->next->next != NULL) {
      count ++;         
      trav = trav->next;
   }
   return count;
}

int numuninitwidthll(struct window *head) {
   int count = 0;
   struct window *trav = head;
   while (trav->next->next != NULL) {
      if (trav->next->width == -1) count ++;
      trav = trav->next;
   }
   return count;
}

/*
 * A window has been added, and its width is -1
 * need to decrease all windows widths, and set the new one
 * to the remainder
 */
void adjustwidthsll(struct window *head, int screensize) {
   //check sum
   int count = sizell(head);

   int numuninit = numuninitwidthll(head);
   if (numuninit == 1) { //adding new window, decrease all widths
      int sum = 0;
      struct window *newnode;
      struct window *trav = head;
      while (trav->next->next != NULL) {
         if (trav->next->width != -1) {
            trav->next->width = ((count - 1) * trav->next->width) / count;
            trav->next->width += ((count -1) * trav->next->width) % count;
            sum += trav->next->width;
         }
         else newnode = trav->next;
         trav = trav->next;
      }

      if (!newnode)
         l("ERROR, adjustwidthsll");
      else newnode->width = screensize - sum;
   } 
   else if (numuninit == 0) { //a node has been removed, increase all widths
      struct window *trav = head;
      while(trav->next->next != NULL) {
         if (count == 0) return; //nothing to do
         trav->next->width = ((count + 1) * trav->next->width) / (count);
         trav->next->width += ((count + 1) * trav->next->width) % (count);
         trav = trav->next;
      }
   }
   else {
      l("ERROR, adjustwidthsll -- more than one node added between calls");
   }
}

void logll(struct window *head) {
   int count = 0;
   lmf("HEAD<-->");
   struct window *trav = head;
   while(trav->next->next != NULL) {
      //lmf("%X:",trav->next->window);
      //char *name;
      //XFetchName(display,trav->next->window,&name);
      lmf("%X<-->",trav->next->window); 
      trav = trav->next;
      count ++;
      if (count > 4) break;
   }
   if (count == 5) l(".....");
   else lf("TAIL");
}
