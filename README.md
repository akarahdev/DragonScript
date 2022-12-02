# DragonScript
DragonScript is a medium-level compiled statically-typed programming language. It can be used for general purpose and I/O on the command line. More features will be coming soon. DragonScript is compiled through the C compiler to be able to turn your script into an executable file.

## Information
Current Version: v0.1-Alpha

To-do (in no particular order):
- [ ] If/else statements
- [ ] While statements
- [ ] Functions
- [ ] Update syntax to be more readable
- [ ] Built-in and addable libraries
- [ ] Add better high-level support


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