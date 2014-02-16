#include <stdarg.h>
#include <string.h>

#include "log.h"

/*
 * Simple debug logging
 */

void initlog() {
   logfile = fopen("/tmp/thewm.log","w");
   l("THEWM STARTED");
}

void closelog() {
   fclose(logfile);
}

void l(const char * msg) {
   fprintf(logfile, "%s\n", msg);
   fflush(logfile);
}

void ld(int val) {
   fprintf(logfile, "%d\n", val);
   fflush(logfile);
}

void lf(const char * fmt, ...) {
   char * f = strdup(fmt);
   va_list args;
   va_start(args, fmt);
   vfprintf(logfile, strcat(f,"\n"), args); 
   va_end(args);
   fflush(logfile);
}

void lmf(const char *fmt, ...) {
   char *f = strdup(fmt);
   va_list args;
   va_start(args,fmt);
   vfprintf(logfile, f, args);
   va_end(args);
   fflush(logfile);
}
