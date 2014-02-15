#include "log.h"

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
