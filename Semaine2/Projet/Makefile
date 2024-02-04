CC=gcc
CFLAGS=-Wall -Werror
CPPFLAGS=-I headers
LDFLAGS=-lm

SRCDIR=sources
OBJDIR=objects
HEADERSDIR=headers
EXECDIR=.
DOCDIR=Documentation

SRCS=$(wildcard $(SRCDIR)/*.c)
HEADERS=$(wildcard $(HEADERSDIR)/*.h)
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAIN_OBJS=$(OBJDIR)/dico.o
EXEC=$(MAIN_OBJS:$(OBJDIR)/%.o=$(EXECDIR)/%)

ifdef DEBUG 
CFLAGS+=-g 
CPPFLAGS+=-DDEBUG
endif

.PHONY : clean

all : $(EXEC) doc

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/dico_tools.o : $(HEADERSDIR)/dico_tools.h $(HEADERSDIR)/structures.h $(HEADERSDIR)/word_tools.h $(HEADERSDIR)/serialization.h
$(OBJDIR)/display.o : $(HEADERSDIR)/display.h $(HEADERSDIR)/structures.h 
$(OBJDIR)/serialization.o : $(HEADERSDIR)/serialization.h $(HEADERSDIR)/structures.h $(HEADERSDIR)/word_tools.h 
$(OBJDIR)/word_tools.o : $(HEADERSDIR)/word_tools.h $(HEADERSDIR)/structures.h

$(MAIN_OBJS): $(HEADERS)

$(EXECDIR)/dico : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

doc:
	@echo "Création de la documentation dans le repertoire Documentation"
	doxygen $(DOCDIR)/doxy-convert.conf 

clean :
	@echo "Nettoyage des fichiers objets, de ses exécutables et de la documentation"
	-rm -r $(OBJDIR)/*.o $(EXEC) Documentation/*/