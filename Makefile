# Makefile template

INCLDIR = ./include
CC = g++
LINK = -lSDL2 -lSDL2_image
CFLAGS = -O2 -g
CFLAGS += -I$(INCLDIR)
CFLAGS += $(LINK)

OBJDIR = ./obj

_DEPS = inputManager.h draw.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o inputManager.o draw.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

f_run: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
