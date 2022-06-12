all: simple

simple:
	gcc -o simple.exe ./Examples/simple.c ./src/glad.c -lopengl32 -lglfw3 -lgdi32
	./simple.exe