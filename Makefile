CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4)

SRC = main.c requestorapp.c requestorappwin.c

OBJS = $(SRC:.c=.o)

all: requestorapp

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

requestorapp: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f requestorapp
