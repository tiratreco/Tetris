CPP    = g++
WINDRES= windres
RM     = rm -f
OBJS   = main.o \
         AppResource.res

LIBS   = -static -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
CFLAGS = -DGLUT_STATIC

.PHONY: Tetris.exe clean clean-after

all: Tetris.exe

clean:
	$(RM) $(OBJS) Tetris.exe

clean-after:
	$(RM) $(OBJS)

Tetris.exe: $(OBJS)
	$(CPP) -Wall -s -o $@ $(OBJS) $(LIBS)

main.o: main.cpp tetris.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

AppResource.res: AppResource.rc
	$(WINDRES) -i AppResource.rc -J rc -o AppResource.res -O coff

