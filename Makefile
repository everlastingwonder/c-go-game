go : bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o
	gcc -o go bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o

bin/go.o : src/go.c defs bin/
	gcc -c src/go.c
	mv go.o bin/

bin/move.o : src/move.c defs bin/
	gcc -c src/move.c
	mv move.o bin/

bin/save.o : src/save.c defs bin/
	gcc -c src/save.c
	mv save.o bin/

bin/display.o : src/display.c defs bin/
	gcc -c src/display.c
	mv display.o bin/

bin/help.o : src/help.c defs bin/
	gcc -c src/help.c
	mv help.o bin/

bin/ :
	if [[ ! ( -d bin/ ) ]] ; then mkdir bin/ ; fi

include/hashes.h : src/calc.c include/chash.h cmdlist.dat bin/
	gcc -o calc src/calc.c
	./calc cmdlist.dat > hashes.h
	mv calc bin/
hash : include/hashes.h

hconf.dat : src/conflict.c include/chash.h cmdlist.dat bin/
	gcc -o conflict src/conflict.c
	./conflict | sed 's/[^0-9]//g' | sort -n | uniq -d > .hconf_tmp
	./conflict | grep --file=.hconf_tmp | sort -n > hconf.dat
	rm .hconf_tmp
	mv conflict bin/
hconf : hconf.dat

include/defs.h : include/chash.h include/hashes.h
defs : include/defs.h

.PHONY : hash hconf defs
