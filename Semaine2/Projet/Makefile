CC=gcc
CFLAGS=-Wall -Werror
SRCS=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJS=$(SRCS:.c=.o)
MAIN_OBJS=dico.o
EXEC=$(MAIN_OBJS:.o=)

ifdef DEBUG 
CFLAGS+=-g 
CPPFLAGS+=-DDEBUG
endif

.PHONY : clean

all : $(EXEC) 

dico_tools.o : dico_tools.h structures.h word_tools.h serialization.h
display.o : display.h structures.h 
serialization.o : serialization.h structures.h word_tools.h 
word_tools.o : word_tools.h structures.h

$(MAIN_OBJS): $(HEADERS)

dico : $(OBJS)
	$(CC) $(OBJS) -lm -o $@

clean : 
	@echo "Nettoyage du répertoire courant"
	-rm *.o $(EXEC)