OS := $(shell uname)
DISTRO := $(shell lsb_release -si)

WIN_CHAIN := $(HOME)/.toolchains/x86_64-w64-mingw32

ARGS := -Wall -03 -0s

ifeq ( $(OS), windows ) 
	LDFLAGS := -lmingw32 -lSDL2main -lSDL2
	EXTENSION := .exe
	KILL := del
else
	LDFLAGS := -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
	EXTENSION :=
	KILL :=  rm -r

endif

.PHONY: all os test main
all: test main

os:
	echo $(OS)

win:
	clang -o The_Gardener _main.c $(ARGS) --target=x86_64-w64-mingw32 --sysroot=$(WIN_CHAIN) -fuse-ld=lld -lSDL2main -lSDL2

test: _test
main: _main
clean:
	$(KILL) _main _test The_Gardener.exe

# platformer: ./example/platformer

_%:
	gcc -o $@ $@.c $(ARGS) $(LDFLAGS)
	./$@$(EXTENSION)
#	$(KILL) $@$(EXTENSION)
