CC = gcc
EXE = snake
DEV_C_FLAGS = -g -Wall
C_FLAGS = $(DEV_C_FLAGS) -std=gnu18 -c
SOURCES=$(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))
SDL_C_FLAGS := $(shell sdl2-config --cflags)
SDL_LIBS := $(shell sdl2-config --libs)

all: $(EXE)

$(EXE): $(notdir $(OBJECTS))
	$(CC) $(SDL_C_FLAGS) $(OBJECTS) -o $@ $(SDL_LIBS)

%.o: src/%.c
	$(CC) $(C_FLAGS) $< -o build/$@

clean:
	rm build/*.o && rm $(EXE)
