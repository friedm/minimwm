#include <stdio.h>

FILE *logfile;

void initlog();
void closelog();
void l(const char *);
void ld(int);
void lf(const char *fmt,...);
void lmf(const char *fmt,...);
