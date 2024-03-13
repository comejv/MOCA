#################
### VARIABLES ###
#################

CC=gcc
CFLAGS= -Wall -Werror -fwrapv -Wno-unused-function
CPPFLAGS = -I$(HEADERSDIR) -I../headers $(OPTGCOV) $(STACKPROTECTOR) -I$(LIBHEADERSDIR)

# Directories for source files, object files, headers, executable files, and Doxygen documentation
SRCDIR=sources
OBJDIR=objects
HEADERSDIR=headers
EXECDIR=.
LIBHEADERSDIR=../libs/headers

# Files names : sources, headers, objects, objects that correspond to an executable file name, and executable files
SRCS=$(wildcard $(SRCDIR)/*.c)
HEADERS=$(wildcard $(HEADERSDIR)/*.h)
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC=testDico

# -fprofile-arcs -ftest-coverage to be able to run test file and gcov
OPTGCOV = -fprofile-arcs -ftest-coverage

# -fstack-protector-all to place canaries in every function and prevent buffer overflow
STACKPROTECTOR = -fstack-protector-all

ifdef DEBUG
CFLAGS+=-g
endif

LDFLAGS= $(OPTGCOV) $(STACKPROTECTOR) -lm

CFLAGS+=-fsanitize=address -g
LDFLAGS+=-fsanitize=address -static-libasan
MAKEARGS+=TEST=1

#############
### RULES ###
#############

.PHONY: clean

all: ensureDirs test

# Rule to make the object files
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Rule to make the executable files
$(EXEC): $(OBJS)
	$(CC) $(OBJS) ../libs/objects/serialization.o ../objects/word_tools.o ../objects/dico_tools.o ../objects/free.o -o $(EXEC) $(LDFLAGS)

# Rule to make the tests
test:
	make clean
	make $(EXEC)
	@echo
	@echo "----- Lancement de l'exécutable des tests et analyse de couverture -----"
	LSAN_OPTIONS="suppressions=.asan_supp" ./testDico
	gcov -b -n -f -s ../sources/ -o ../$(OBJDIR) -c word_tools.c
	gcov -b -n -f -s ../libs/sources/ -o ../libs/$(OBJDIR) -c serialization.c
	gcov -b -n -f -s ../sources/ -o ../$(OBJDIR) -c dico_tools.c

# Rule to create all needed directories (-p to disable errors if they already exist)
ensureDirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(EXECDIR)

# Rule to clean the workspace
clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)
	rm -rf $(OBJDIR)/*.gc*
