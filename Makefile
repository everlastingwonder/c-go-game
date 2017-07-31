go : go.o move.o save.o display.o help.o
	gcc -o go go.o move.o save.o display.o help.o

go.o : go.c defs.h
	gcc -c go.c

move.o : move.c defs.h
	gcc -c move.c

save.o : save.c defs.h
	gcc -c save.c

display.o : display.c defs.h
	gcc -c display.c

help.o : help.c
	gcc -c help.c
