all: main

main:
	gcc -o main main.c -Wall -lmingw32 -lSDL2main -lSDL2
	./main.exe
	del main.exe

platformer:
	gcc -o platformer ./example/platformer.c -Wall -lmingw32 -lSDL2main -lSDL2
	./platformer.exe
	del platformer.exe