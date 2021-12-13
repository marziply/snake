CC = gcc
EXE = snake
BUILD_DIR = ./build
C_FLAGS = -std=gnu18 -c
DEV_C_FLAGS = -g -Wall
SOURCES=$(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))
SDL_C_FLAGS := $(shell sdl2-config --cflags) 
SDL_LIBS := $(shell sdl2-config --libs) -lSDL2_ttf

all: $(EXE)

debug: C_FLAGS += $(DEV_C_FLAGS)
debug: $(EXE)

$(EXE): $(notdir $(OBJECTS))
	$(CC) $(SDL_C_FLAGS) $(OBJECTS) $(SDL_LIBS) -o $@

%.o: src/%.c
	@mkdir -p $(BUILD_DIR)

	$(CC) $(C_FLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXE)
