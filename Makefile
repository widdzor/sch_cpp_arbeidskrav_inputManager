# Makefile template

INCLDIR = ./include
CC = g++
LINK = -lSDL2 -lSDL2_image
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
CFLAGS += $(LINK)

OBJDIR = ./obj

_DEPS = inputManager.h#list header files here
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

f_run: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
