build:
	clang -std=c99 -Wall -Wno-unused-function source/main.c `pkg-config --libs --cflags raylib` -o console

.PHONY:  build
