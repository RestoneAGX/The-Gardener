all: build run clean

build:
	gcc -o test program.c ./tools/glad.c -lopengl32 -lglfw3 -lgdi32

run:
	./test.exe

clean:
	del test.exe

simple:
	gcc -o simple.exe ./Examples/simple.c ./tools/glad.c -lopengl32 -lglfw3 -lgdi32
	./simple.exe
	del simple.exe