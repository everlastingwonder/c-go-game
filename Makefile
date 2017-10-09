# Main target; compiles the actual go executable #
# and puts it in the root project directory (as  #
# opposed to bin/ with the other compiled files) #

go : bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o
	gcc -o go bin/go.o bin/move.o bin/save.o bin/display.o bin/help.o



# Partial compilation targets for go.c and its dependencies #

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



# Stupid target to add a bin/ directory if it doesn't  #
# exist (so that my .gitignore isn't ugly as all hell) #

bin/ :
	if [[ ! ( -d bin/ ) ]] ; then mkdir bin/ ; fi



# Target that generates a header with command hash  #
# macros (for writing switch statements with chash) #

include/hashes.h : src/calc.c include/chash.h include/cmdlist bin/
	gcc -o calc src/calc.c
	./calc include/cmdlist > include/hashes.h
	mv calc bin/
hash : include/hashes.h



# Target to generate a list of commands from #
# cmdlist that have conflicting hash values  #

hconf.dat : src/conflict.c include/chash.h include/cmdlist bin/
	gcc -o conflict src/conflict.c
	./conflict | sed 's/[^0-9]//g' | sort -n | uniq -d > .hconf_tmp
	./conflict | grep --file=.hconf_tmp | sort -n > hconf.dat
	rm .hconf_tmp
	mv conflict bin/
hconf : hconf.dat



# Target for defs.h, just to make other targets slightly neater #

include/defs.h : include/chash.h include/hashes.h
defs : include/defs.h



# Special target to tell make that hash, hconf, and defs #
# are "fake" targets that are just there for convenience #

.PHONY : hash hconf defs
