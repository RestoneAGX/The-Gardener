OS := $(shell uname)
DISTRO := $(shell lsb_release -si)

ifeq ( $(OS), windows ) 
	LDFLAGS := -Wall -lmingw32 -lSDL2main -lSDL2 -O3 -Os
	EXTENSION := .exe
	KILL := del
else
	LDFLAGS := -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
	EXTENSION :=
	KILL :=  rm -f

endif

.PHONY: all os test main
all: test main

os:
	echo $(OS)

win:
	clang -o testing _test.c -target x86_64-win32
test: _test
main: _main
clean:
	rm -r _main _test

# platformer: ./example/platformer

_%:
	gcc -o $@ $@.c -Wall $(LDFLAGS)
	./$@$(EXTENSION)
#	$(KILL) $@$(EXTENSION)
