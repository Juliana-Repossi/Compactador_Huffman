TARGET := Compacta Descompacta
LIBS := -lm
CFLAGS := -g -O3
OBJDIR := obj/
SRCDIR := src/
INCLUDEDIR := include/
INCLUDE_PATHS := -Iinclude
COMPACTA := client/compacta.c
DESCOMPACTA := client/descompacta.c
CC := gcc

all: $(TARGET)

SRC = $(wildcard $(SRCDIR)*.c)
HEADERS = $(wildcard $(INCLUDEDIR)*.h)

COM = $(OBJDIR)$(basename $(notdir $(COMPACTA)))
DES = $(OBJDIR)$(basename $(notdir $(DESCOMPACTA)))

OBJECTS1 := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
OBJECTS1 += $(COM).o

OBJECTS2 := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
OBJECTS2 += $(DES).o

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@ mkdir -p $(OBJDIR)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(COM).o: $(COMPACTA)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(DES).o: $(DESCOMPACTA)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

Compacta: $(OBJECTS1)
	$(CC) $(INCLUDE_PATHS) $(OBJECTS1) $(LIBS) -o $@

Descompacta: $(OBJECTS2)
	$(CC) $(INCLUDE_PATHS) $(OBJECTS2) $(LIBS) -o $@

clean:
	-rm -f -r obj
	-rm -f *.o
	-rm -f $(TARGET)
