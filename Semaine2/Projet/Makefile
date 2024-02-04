CC=gcc
CFLAGS=-Wall -Werror
CPPFLAGS=-I headers -I libs/display_lib/headers -I libs/serialization_lib/headers
LDFLAGS=-lm 
# -Wl,-rpath,libs/display_lib/lib -Wl,-rpath,libs/serialization_lib/lib ne semble pas fonctionner (cannot find -ldisplay, cannot find -lserialization)
ifdef STATIC
LDFLAGS+=-L libs/display_lib/lib -l:libdisplay.a -L libs/serialization_lib/lib -l:libserialization.a
else
LDFLAGS+=-L libs/display_lib/lib -l:libdisplay.so -L libs/serialization_lib/lib -l:libserialization.so
endif

SRCDIR=sources
OBJDIR=objects
HEADERSDIR=headers
EXECDIR=.
DOCDIR=documentation

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

all : lib $(EXEC) doc 

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/dico_tools.o : $(HEADERSDIR)/dico_tools.h $(HEADERSDIR)/structures.h $(HEADERSDIR)/word_tools.h libs/serialization_lib/headers/serialization.h
$(OBJDIR)/word_tools.o : $(HEADERSDIR)/word_tools.h $(HEADERSDIR)/structures.h

$(MAIN_OBJS): $(HEADERS)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

lib:
	@echo "Compilation des librairies"
ifdef STATIC
	cd libs && $(MAKE) clean && $(MAKE) STATIC=1
else 
	cd libs && $(MAKE) clean && $(MAKE)
endif

doc:
	@echo "Création de la documentation dans le repertoire documentation"
	doxygen $(DOCDIR)/doxy-convert.conf 

clean :
	@echo "Nettoyage des fichiers objets, de ses exécutables et de la documentation"
	-rm -r $(OBJDIR)/*.o $(EXEC) $(DOCDIR)/*/
ifdef LIBCLEAN
	@echo "Nettoyage des librairies"
	cd libs && $(MAKE) clean
endif