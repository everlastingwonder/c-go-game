go : bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o
	gcc -o go bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o

bin/go.o : go.c defs.h chash.h hashes.h
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

bin/help.o : help.c defs.h
	gcc -c help.c
	mv help.o bin/

hashes.h : calc.c chash.h cmdlist.dat
	gcc -o calc calc.c
	./calc cmdlist.dat > hashes.h
	mv calc bin/
