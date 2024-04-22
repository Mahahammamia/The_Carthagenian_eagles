prog: main.o minimap.o
	gcc  minimap.c main.c -o prog -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image 
main.o:main.c
	gcc -c main.c
minimap.o:minimap.c
	gcc -c minimap.c
