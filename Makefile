CC = gcc
EMCC = emcc

#-------------------------------  FLAGS  -------------------------------------#
FLAGS= -Wall -Wextra -Wconversion -Wpedantic -Wformat=2\
        -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes\
        -Wold-style-definition -Wredundant-decls -Wnested-externs\
        -Wmissing-include-dirs -O3 -std=c99

EMFLAGS=$(FLAGS)
EMFLAGS+=-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png", "jpg"]'

# GCC warnings that Clang or emcc doesn't provide:
CFLAGS=$(FLAGS)
CFLAGS=-Wjump-misses-init -Wlogical-op

#-----------------------------------------------------------------------------#

TARGET=build/main.exe
EMOUT = index.js

SDL_OBJDIR=src/obj/sdl
EMS_OBJDIR=src/obj/ems
SRCDIR=src
INCDIR=-Iinclude

_OBJ= main.o sketch.o loop.o once.o event.o MEOW.o\
      getpath.o whereami.o vector.o
SDL_OBJ=$(addprefix $(SDL_OBJDIR)/, $(_OBJ))
EMS_OBJ=$(addprefix $(EMS_OBJDIR)/, $(_OBJ))

LIB=-lm
SDL_LIB=-lSDL2 -lSDL2 -lSDL2_image
DEFINE= -DSDL_MAIN_HANDLED -DSTB_RECT_PACK_IMPLEMENTATION\
        -DSTB_TRUETYPE_IMPLEMENTATION -DSTBTTF_IMPLEMENTATION

ASSETS=build/assets
EMFILE=index.data index.js index.wasm


.PHONY:default
default:
	echo try with ems or sdl

.PHONY:ems
ems: $(EMS_OBJ)
	$(EMCC) -o $(EMOUT) $^ $(EMFLAGS) --preload-file $(ASSETS) $(LIB)

$(EMS_OBJDIR)/%.o: $(SRCDIR)/%.c
	$(EMCC) -c -o $@ $< $(EMFLAGS) $(DEFINE) $(INCDIR)

.PHONY:sdl
sdl: $(SDL_OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(SDL_LIB)

$(SDL_OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(DEFINE) $(INCDIR)

.PHONY:run
run:
	build/main.exe

.PHONY:drm
drm:
	drmemory build/main.exe

.PHONY:clean
clean:
	del /f $(subst /,\,$(TARGET) $(EMOUT) $(SDL_OBJDIR) $(EMS_OBJDIR))
