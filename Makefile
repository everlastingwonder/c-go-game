go : bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o
	gcc -o go bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o

bin/go.o : go.c defs
	gcc -c go.c
	mv go.o bin/

bin/move.o : move.c defs
	gcc -c move.c
	mv move.o bin/

bin/save.o : save.c defs
	gcc -c save.c
	mv save.o bin/

bin/display.o : display.c defs
	gcc -c display.c
	mv display.o bin/

bin/help.o : help.c defs
	gcc -c help.c
	mv help.o bin/

include/hashes.h : calc.c include/chash.h cmdlist.dat
	gcc -o calc calc.c
	./calc cmdlist.dat > hashes.h
	mv calc bin/
hash : include/hashes.h

hconf.dat : conflict.c include/chash.h cmdlist.dat
	gcc -o conflict conflict.c
	./conflict | sed 's/[^0-9]//g' | sort -n | uniq -d > .hconf_tmp
	./conflict | grep --file=.hconf_tmp | sort -n > hconf.dat
	rm .hconf_tmp
	mv conflict bin/
conf : hconf.dat

include/defs.h : include/chash.h include/hashes.h
defs : include/defs.h

.PHONY : hash hconf defs
