CC = gcc
EXE = snake
DEV_C_FLAGS = -g -Wall
# -fsanitize=address
BUILD_DIR = ./build
C_FLAGS = $(DEV_C_FLAGS) -std=gnu18 -c
SOURCES=$(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))
SDL_C_FLAGS := $(shell sdl2-config --cflags) 
SDL_LIBS := $(shell sdl2-config --libs) -lSDL2_ttf

all: $(EXE)

$(EXE): $(notdir $(OBJECTS))
	$(CC) $(DEV_C_FLAGS) $(SDL_C_FLAGS) $(OBJECTS) -o $@ $(SDL_LIBS)

%.o: src/%.c
	@mkdir -p $(BUILD_DIR)

	$(CC) $(C_FLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXE)
