#################
### VARIABLES ###
#################

CC=gcc
CFLAGS=-Wall -Werror

# Directories for source files, object files, headers, executable files, and Doxygen documentation
SRCDIR=sources
OBJDIR=objects
HEADERSDIR=headers
EXECDIR=.

# Files names : sources, headers, objects, objects that correspond to an executable file name, and executable files
SRCS=$(wildcard $(SRCDIR)/*.c)
HEADERS=$(wildcard $(HEADERSDIR)/*.h)
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAIN_OBJS=$(OBJDIR)/testDico.o
EXEC=$(MAIN_OBJS:$(OBJDIR)/%.o=$(EXECDIR)/%)

# -fprofile-arcs -ftest-coverage to be able to run test file and gcov
OPTGCOV = -fprofile-arcs -ftest-coverage

CFLAGS= -I$(HEADERSDIR) -I../headers -Wall $(OPTGCOV)
LDFLAGS= $(OPTGCOV)


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
	$(CC) $(OBJS) ../objects/word_tools.o -o $(EXEC) $(LDFLAGS)

# Rule to make the tests
test:
	make clean
	make $(EXEC)
	./testDico
	@gcov -b -n -m -f -s ../sources/ -o ../$(OBJDIR) -c word_tools.c

# Rule to create all needed directories (-p to disable errors if they already exist)
ensureDirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(EXECDIR)

# Rule to clean the workspace
clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)
	rm -rf $(OBJDIR)/*.gc*
