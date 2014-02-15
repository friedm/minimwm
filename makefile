thewm: *.c *.h
	gcc -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -o thewm thewm.c input.c events.c utils.c log.c

all: thewm

run: thewm
	startx
	cat /tmp/thewm.log
