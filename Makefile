
make:
	gcc ./src/gameRaylib.c ./src/graphics.c ./src/gamerules.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./a.out