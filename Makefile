build:
	clang -std=c99 source/main.c `pkg-config --libs --cflags raylib` -o console

.PHONY:  build
