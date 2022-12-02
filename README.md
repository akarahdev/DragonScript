# DragonScript
DragonScript is a medium-level compiled statically-typed programming language. It can be used for general purpose and I/O on the command line. More features will be coming soon. DragonScript is compiled through the C compiler to be able to turn your script into an executable file.
Please keep in mind DragonScript is in an extremely early alpha. It is not ready to be used in production in any sort of way.

## Installation

To install, you will need to download the latest "dragon.exe" and a GCC compiler.
- GCC Compiler: https://winlibs.com/
- dragon.exe: Find the latest on our Releases page, or compile it yourself.

After that, you can download the "dragonsetup.bat" to quickly add dragon to your PATH.
A folder will be made at C:/DragonScript. Please make sure this folder is empty / does not exist.
You will have to put dragon.exe inside manually. A setup wizard will be coming soon.

## Usage

Make a file named anything, ending in ".ds". Inside the file, start typing your DragonScript code and save.
Then, go to a command line and type "dragon <file name>", e.g "dragon MyScript.ds".
It should compile to C and then run. For now, it will display C compiler errors, but this will be fixed later.

## Information
Current Version: v0.1-Alpha

To-do (in no particular order):
- [ ] If/else statements
- [ ] While statements
- [ ] Functions
- [ ] Better error handling
- [ ] Update syntax to be more readable
- [ ] Built-in and addable libraries
- [ ] Make it easier to use at a high-level
- [ ] Low level memory support


## Examples
Hello World
```
; define strings "hello" and "world"
str hello
str world
; set the value of strings "hello" and "world"
setstr hello = "Hello "
setstr world = "world!"
; print them to console
print "$str{hello} $str{world}"
; free the strings (optional)
free hello
free world
```

Basic Arithmetic
```
; define x and y
int x
int y
; set x and y to numbers
set x = 5
set y = 10
; print the added 2 numbers to console
print "5 + 10 is $int{x + y}"
; free integers (optional)
free x
free y
```

Input/Output
```
; define name
str name
; ask for name
print "What's your name?"
query name
; print name to console
print "Hello $str{name}!"
; free strings (optional)
free name
```

## DIY Compilation
You can also compile this yourself!

1. Download the "main.c" and "dragon.h" files.
2. Install the gcc compiler.
