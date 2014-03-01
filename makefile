minimwm: *.c *.h
	gcc -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -o minimwm minimwm.c input.c actions.c events.c utils.c log.c tile.c screen.c desktop.c window.c

all: minimwm

run: minimwm
	startx
	cat /tmp/minimwm.log
