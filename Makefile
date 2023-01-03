build:
	clang -std=c99 -Wall -Werror source/main.c `pkg-config --libs --cflags raylib` -o console

.PHONY:  build
