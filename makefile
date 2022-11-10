OS := $(shell uname)

ifeq ( $(OS), windows ) 
	LDFLAGS := -Wall -lmingw32 -lSDL2main -lSDL2
	EXTENSION := .exe
	KILL := del
else
	LDFLAGS := -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
	EXTENSION :=
	KILL :=  rm -f

endif

all: test main

os:
	echo $(OS)

test: test_main

main: $@

# platformer: ./example/platformer

%:
	gcc -o $@ $@.c -Wall $(LDFLAGS)
	./$@$(EXTENSION)
	$(KILL) $@$(EXTENSION)
