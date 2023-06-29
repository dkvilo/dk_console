build:
	clang -std=c99 -Wall -Werror source/main.c `pkg-config --libs --cflags raylib` -o console
wasm:
	emcc -o wasm-build/console.html source/main.c -Os -Wall ./lib/wasm32/libraylib.a -I. `pkg-config --cflags raylib` -L. -s ASYNCIFY -s ASSERTIONS=1 -s USE_GLFW=3 -s ALLOW_MEMORY_GROWTH -s FORCE_FILESYSTEM=1 -DPLATFORM_WEB --preload-file Resources

.PHONY:  build wasm
