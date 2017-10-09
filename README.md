# CGG (C Go Game)
A program for playing the board game Go from the command line. Currently includes save/load functionality and an ~~utterly godawful~~ interface; secondary (read: critical) features such as documentation and actual checking of game rules coming soon.

## Useful `make` Targets
`$ make`<br />
Compiles the main `go` executable and puts the binary in the project root directory

`$ make go`<br />
Same as `make` with no arguments (`go` is the default target since it's the first one in `Makefile`)

`$ make hash`<br />
Generates a header file (in the `include/` directory) containing macros for writing `switch` statements with `chash`

`$ make hconf`<br />
Generates a file listing any commands from `cmdlist` with conflicting `chash` values

## Glossary
|Term |                                                 Definition                                                 |
|:---:|:-----------------------------------------------------------------------------------------------------------|
| CGG | C Go Game                                                                                                  |
| GCC | Gnu Compiler Collection (used to compile binaries for this project during testing but otherwise unrelated) |
| GGC | DNA sequence coding for the amino acid glycine                                                             |
