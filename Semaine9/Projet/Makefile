#################
### VARIABLES ###
#################

CC=gcc
CFLAGS=-Wall -Werror -fwrapv
# -I option used here to tell the compiler in which folders to search for the headers (main headers + libs headers)
CPPFLAGS=-I headers -I $(LIBDIR)/headers 
# arguments passed to the sub Makefile (along with the $(MAKE) command)

# -Wl,-rpath,libs/libs/ add a directory to find our libraries (allows us to omit the use of "export LD_LIBRARY_PATH=./libs/libs/:$LD_LIBRARY_PATH")
LDFLAGS=-Wl,-rpath,$(LIBDIR)/libs/
# If STATIC is defined, we want to generate static libraries, whose name end with ".a" and force a static link with libs display and serialization
# Otherwise, we want to generate shared libraries, whose name end with ".so" and force a dynamic link with libs display and serialization
ifdef STATIC
LIBEXT=.a
else
LIBEXT=.so
endif
# Libraries specific options : 
# -L to give the libraries path name
# -l to give the name of libraries files (with the ":" syntax allowing us to specify the full name, including the right suffix depending on
# whether we want to generate static or dynamic libraries)
LDFLAGS+=-L $(LIBDIR)/libs -l:libdisplay$(LIBEXT) -l:libserialization$(LIBEXT) -lm

# Directories for source files, object files, headers, executable files, and Doxygen documentation
SRCDIR=sources
OBJDIR=objects
HEADERSDIR=headers
LIBDIR=libs
EXECDIR=.
DOCDIR=documentation
RESDIR=resultats
TESTDIR=auto_tests
AFLOUTDIR=$(TESTDIR)/afl_out
PROFILERDIR=profiler

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
ifeq ($(DEBUG),LIBS)
CPPFLAGS+=-DFDEBUG=1
else ifeq ($(DEBUG),DICO)
CPPFLAGS+=-DFDEBUG=2
else ifeq ($(DEBUG),WORD)
CPPFLAGS+=-DFDEBUG=3
else ifeq ($(DEBUG),HASH)
CPPFLAGS+=-DFDEBUG=4
else
CPPFLAGS+=-DFDEBUG=0
endif
endif

# Instrumentation librairies
# one variable per test target
# changing here will affect all other makefiles
UNITEST=GCOV=1

SYSTEST=GCOV=1 ASAN=1

AFLTEST=AFL_USE_ASAN=1 AFL_DONT_OPTIMIZE=1 ASAN=1 AFL=1

ifdef GCOV 
	OPTGCOV=-fprofile-arcs -ftest-coverage
	CFLAGS+=$(OPTGCOV)
	LDFLAGS+=$(OPTGCOV)
endif

# always stack protector
CFLAGS+=-fstack-protector-all
LDFLAGS+=-fstack-protector-all

ifdef ASAN
	CFLAGS+=-fsanitize=address -g
	LDFLAGS+=-fsanitize=address -static-libasan
endif

ifdef AFL
	ifeq ($(shell which $(AFLDIR)/afl-gcc-fast 2>/dev/null), )  # Check if afl-gcc-fast exists
		CC=$(AFLDIR)/afl-gcc
	else
		CC=$(AFLDIR)/afl-gcc-fast
	endif
endif

ifdef GPROF
	CFLAGS += -pg
	LDFLAGS += -pg
endif

#############
### RULES ###
#############

.PHONY : ensureDirs showCov clean cleanall unitest systest afltest gprof

# Default target
all : lib ensureDirs message $(EXEC)

# Rule to organize the output
message : 
	@echo 
	@echo "----- Compilation et génération du programme principal -----"

# Rule to make the object files
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Specification of the headers that every object file depends on (in case only preprocessor instructions are modified)
$(OBJDIR)/dico_tools.o : $(HEADERSDIR)/dico_tools.h $(HEADERSDIR)/structures.h $(HEADERSDIR)/word_tools.h $(LIBDIR)/headers/serialization.h
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
	@echo
	@echo "----- Nettoyage et compilation des librairies -----"
	$(MAKE) -C $(LIBDIR) clean
	$(MAKE) -C $(LIBDIR) 

# Rule to compile and generate tests files, and show results
unitest:
	@echo "UNITESTS : $(UNITEST)"
	$(MAKE) cleanall
	$(MAKE) $(UNITEST)
	@echo
	@echo "----- Compilation des tests + leurs lancements -----"
	$(MAKE) -C $(TESTDIR) $(UNITEST)

systest:
	$(MAKE) cleanall
	$(MAKE) $(SYSTEST)
	bash auto_tests/systests.bash
ifeq ($(findstring GCOV=1,$(SYSTEST)),GCOV=1)
	$(MAKE) showCov
endif

afltest:
	$(MAKE) cleanall
	$(MAKE) $(AFLTEST)
	AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 AFL_SKIP_CPUFREQ=1 AFL_USE_ASAN=1 afl-fuzz -D -i ./exemples/afl/ -o $(AFLOUTDIR) $(EXEC) @@

gprof:
	$(MAKE) cleanall
	$(MAKE) GPROF=1 STATIC=1
	$(EXEC) exemples/longtext.txt > /dev/null
ifdef GRAPH
		gprof $(EXEC) | $(PROFILERDIR)/gprof2dot.py | dot -Tpng -o $(PROFILERDIR)/resultatgprof.png
endif
	gprof $(EXEC)

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
	@mkdir -p $(RESDIR)
	@mkdir -p $(AFLOUTDIR)

showCov:
	@gcov -b -o $(OBJDIR) -c $(SRCS)

# Rule to clean the workspace + libs + auto_test
cleanall :
	@echo "----- Nettoyage des objets, des exécutables et de la documentation -----"
	-rm -r $(OBJDIR)/*.o $(EXEC) $(DOCDIR)/*/ 2> /dev/null
	-rm $(OBJDIR)/*.gc* 2> /dev/null
	-rm gmon.out 2> /dev/null
	-rm *.gcov 2> /dev/null
	@echo
	@echo "----- Nettoyage des librairies -----"
	$(MAKE) -C $(LIBDIR) clean
	@echo
	@echo "----- Nettoyage du repertoire auto_tests -----"
	$(MAKE) -C $(TESTDIR) clean
	-rm -r $(AFLOUTDIR)
	@echo "----- Nettoyage des fichiers images du profiler -----"
	-rm $(PROFILERDIR)/resultatgprof.png
	-rm massif.*

# Rule to clean the workspace
# The LIBCLEAN option can be specified in command line to also clean the libraries (libs) subdirectory (through the sub Makefile)
# The TESTCLEAN option can be specified in command line to also clean the auto tests (auto_tests) subdirectory (through the sub Makefile)
clean :
	@echo "----- Nettoyage des objets, des exécutables et de la documentation -----"
	-rm -r $(OBJDIR)/*.o $(EXEC) $(DOCDIR)/*/ 2> /dev/null
	-rm $(OBJDIR)/*.gc* 2> /dev/null
ifdef LIBCLEAN
	@echo
	@echo "----- Nettoyage des librairies -----"
	$(MAKE) -C $(LIBDIR) clean
endif
ifdef TESTCLEAN
	@echo
	@echo "----- Nettoyage du repertoire auto_tests -----"
	$(MAKE) -C $(TESTDIR) clean
endif

