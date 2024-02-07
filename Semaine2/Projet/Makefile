#################
### VARIABLES ###
#################

CC=gcc
CFLAGS=-Wall -Werror
# -I option used here to tell the compiler in which folders to search for the headers (main headers + libs headers)
CPPFLAGS=-I headers -I libs/headers
# -Wl,-rpath,libs/display_lib/lib -Wl,-rpath,libs/serialization_lib/lib doesn't seem to work (cannot find -ldisplay, cannot find -lserialization)
MAKEARGS=
# If STATIC is defined, we want to generate static libraries, whose name end with ".a"
# Otherwise, we want to generate shared libraries, whose name end with ".so"
ifdef STATIC
LIBEXT=.a
MAKEARGS+=STATIC=1
else
LIBEXT=.so
endif
# Libraries specific options : 
# -L to give the libraries path name
# -l to give the name of libraries files (with the ":" syntax allowing us to specify the full name, including the right suffix depending on
# whether we want to generate static or dynamic libraries)
LDFLAGS=-L libs/libs -l:libdisplay$(LIBEXT) -l:libserialization$(LIBEXT) -lm

# Directories for source files, object files, headers, executable files, and Doxygen documentation
SRCDIR=sources
OBJDIR=objects
HEADERSDIR=headers
EXECDIR=.
DOCDIR=documentation

# Files names : sources, headers, objects, objects that correspond to an executable file name, and executable files
SRCS=$(wildcard $(SRCDIR)/*.c)
HEADERS=$(wildcard $(HEADERSDIR)/*.h)
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAIN_OBJS=$(OBJDIR)/dico.o
EXEC=$(MAIN_OBJS:$(OBJDIR)/%.o=$(EXECDIR)/%)

# Debug mode : 
# -g to be able to run gdb
# -DDEBUG to define the DEBUG macro in source files
# DEBUG=1 option passed to the sub Makefile (used to generate libraries) to activate debug mode in libraries source files too
ifdef DEBUG 
CFLAGS+=-g 
CPPFLAGS+=-DDEBUG
MAKEARGS+=DEBUG=1
endif

#############
### RULES ###
#############

.PHONY : clean

# Default target
all : lib ensureDirs message $(EXEC) doc 

# Rule to organize the output
message : 
	@echo 
	@echo "----- Compilation et génération du programme principal -----"

# Rule to make the object files
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Specification of the headers that every object file depends on (in case only preprocessor instructions are modified)
$(OBJDIR)/dico_tools.o : $(HEADERSDIR)/dico_tools.h $(HEADERSDIR)/structures.h $(HEADERSDIR)/word_tools.h libs/headers/serialization.h
$(OBJDIR)/word_tools.o : $(HEADERSDIR)/word_tools.h $(HEADERSDIR)/structures.h

# Special case for main objects files because they depend on all headers
$(MAIN_OBJS): $(HEADERS)

# Rule to generate executable files
$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Rule to compile and generate libraries (using the sub Makefile in libs)
# && is used to execute several commands in a row and in the same shell (otherwise every process is run on a different shell)
# $(MAKE) is a standard variable containing the make command (used to avoid conflicts with other potentially defined make variables)
lib:
	@echo "----- Nettoyage et compilation des librairies -----"
	cd libs && $(MAKE) clean && $(MAKE) $(MAKEARGS)

# Rule to generate automatic documentation (via Doxygen, based on the configuration file located in DOCDIR)
doc:
	@echo
	@echo "----- Création de la documentation dans le repertoire documentation -----"
	doxygen $(DOCDIR)/doxy-convert.conf 

# Rule to create all needed directories (-p to disable errors if they already exist)
ensureDirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(EXECDIR)
	@mkdir -p $(DOCDIR)

# Rule to clean the workspace
# The LIBCLEAN option can be specified in command line to also clean the libraries (libs) subdirectory (through the sub Makefile)
clean :
	@echo "----- Nettoyage des objets, des exécutables et de la documentation -----"
	-rm -r $(OBJDIR)/*.o $(EXEC) $(DOCDIR)/*/
ifdef LIBCLEAN
	@echo
	@echo "----- Nettoyage des librairies -----"
	cd libs && $(MAKE) clean
endif