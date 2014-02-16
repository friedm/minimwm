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
   if (tail->prev->prev == NULL) {
      return NULL; //empty ll
   }
   if (current->prev->prev != NULL) {
      return current->prev; //there is another element to the left
   }
   else {
      return tail->prev;
   }
}

void logll(struct window *head) {
   lmf("HEAD-->");
   struct window *trav = head;
   while(trav->next->next != NULL) {
      //lmf("%X:",trav->next->window);
      char *name;
      XFetchName(display,trav->next->window,&name);
      lmf("%s-->",name); 
      trav = trav->next;
   }
   lf("TAIL");
}
