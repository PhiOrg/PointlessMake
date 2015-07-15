How should show a pointlessmake.pam file?
=========
If you want to create a static library with PointlessMake then the file should look like:
```
StaticLibrary name.a \* or name.la *\
compiler compiler_name \* this keyword is compulsory *\
cflags \* this keyword is optional *\
files  \* this keyword is compulsory *\
```

If you add the ldflags keyword in the StaticLibrary body then you receive a error. The cflags and files keywords can appear several times.

E.g.:
```
StaticLibrary prime.la
compiler g++
cflags -std=c++11
cflags -Wall
files src/prime.cpp
files src/otherfile.cpp
```
But this file can be rewritten like:
```
StaticLibrary prime.la
compiler g++
cflags -std=c++11 -Wall
files src/prime.cpp src/otherfile.cpp
```

If you want to create a shared object the file should look like:
```
SharedObject name.so
compiler compiler_name \* this keyword is compulsory *\
cflags \* this keyword is optional *\
ldflags \* this keyword is optional *\
files  \* this keyword is compulsory *\
```
E.g:
```
SharedObject prime.so
compiler g++
cflags -std=c++11 -Wall
files src/prime.cpp
```

For a executable the file should look like:
```
Executable name
compiler compiler_name \* this keyword is compulsory *\
cflags \* this keyword is optional *\
ldflags \* this keyword is optional *\
files  \* this keyword is compulsory *\
```
E.g:
```
Executable name
compiler g++
cflags -std=c++11 -Wall
ldflags -lm
files src/main.cpp
```

And an example for an complex project:
```
StaticLibrary libgame.la
compiler gcc
cflags -std=c99
files src/file1.c src/file2.c src/file3.c
files src/file4.c src/file5.c

StaticLibrary libgameAI.la
compiler g++
cflags -std=c++11 -Wall
files src/AI/file1.cpp src/AI/file2.cpp

Executable game
compiler g++
cflags -std=c++11 -Wall
ldflags bin/libgame.la bin/libgameAI.la
files src/main.cpp
```



How works PointlessMake?
=========
PointlessMake is an simple auto-tools. PointlessMake mey be used just from terminal. When he is started he checks if in the current directory exists a file with the name pointlessmake.pam, if this file doesn't exists then PointlessMake stops.
If the pointlessmake.pam file exists then he checks if exists the src directory. If this directory doesn't exists then PointlessMake stops, else he begins to process the pointlessmake.pam file.

PointlessMake will create a directory named bin where he will add all object files and all static libraries, shared objects and executables.
