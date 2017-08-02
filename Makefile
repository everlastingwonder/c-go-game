go : bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o
	gcc -o go bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o

bin/go.o : go.c defs.h
	gcc -c go.c
	mv go.o bin/

bin/move.o : move.c defs.h
	gcc -c move.c
	mv move.o bin/

bin/save.o : save.c defs.h
	gcc -c save.c
	mv save.o bin/

bin/display.o : display.c defs.h
	gcc -c display.c
	mv display.o bin/

<<<<<<< HEAD
help.o : help.c defs.h
=======
bin/help.o : help.c
>>>>>>> Edit Makefile so .o files go in bin/ (plus a few bug fixes)
	gcc -c help.c
	mv help.o bin/
