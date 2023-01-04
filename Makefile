
make:
	gcc src/main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -fsanitize=address -o ChessGame
	./ChessGame

clean:
	rm ChessGame
	indent src/*c -linux -nut -i2
	indent src/*h -linux -nut -i2
	rm src/*~
