CC=gcc
CFLAGS=-Wall -Werror
CPPFLAGS=-I headers -I libs/headers
# -Wl,-rpath,libs/display_lib/lib -Wl,-rpath,libs/serialization_lib/lib ne semble pas fonctionner (cannot find -ldisplay, cannot find -lserialization)
MAKEARGS=
ifdef STATIC
LIBEXT=.a
MAKEARGS+=STATIC=1
else
LIBEXT=.so
endif
LDFLAGS=-L libs/libs -l:libdisplay$(LIBEXT) -l:libserialization$(LIBEXT) -lm

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
MAKEARGS+=DEBUG=1
endif

.PHONY : clean

all : lib ensureDirs $(EXEC) doc 

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/dico_tools.o : $(HEADERSDIR)/dico_tools.h $(HEADERSDIR)/structures.h $(HEADERSDIR)/word_tools.h libs/headers/serialization.h
$(OBJDIR)/word_tools.o : $(HEADERSDIR)/word_tools.h $(HEADERSDIR)/structures.h

$(MAIN_OBJS): $(HEADERS)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

lib:
	@echo "Compilation des librairies"
	cd libs && $(MAKE) clean && $(MAKE) $(MAKEARGS)

doc:
	@echo "Création de la documentation dans le repertoire documentation"
	doxygen $(DOCDIR)/doxy-convert.conf 

ensureDirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(EXECDIR)
	@mkdir -p $(DOCDIR)

clean :
	@echo "Nettoyage des fichiers objets, de ses exécutables et de la documentation"
	-rm -r $(OBJDIR)/*.o $(EXEC) $(DOCDIR)/*/
ifdef LIBCLEAN
	@echo "Nettoyage des librairies"
	cd libs && $(MAKE) clean
endif