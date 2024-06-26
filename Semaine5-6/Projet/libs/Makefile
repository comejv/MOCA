#################
### VARIABLES ###
#################

CC := gcc
CFLAGS := -Wall -Werror -fwrapv
# If STATIC is undefined, we use the -fPIC (Position Independent Code) compiler option to be able to generate shared libraries afterwards
# and we add the -lm linker option to get libmath (since we're only going to use gcc in the case of shared libraries, we won't need -lm for 
# static ones)
ifndef STATIC
CFLAGS += -fPIC
LDFLAGS := -lm
endif
# -I option used here to tell the compiler in which folders to search for the headers (main headers + libs headers)
CPPFLAGS := -I headers -I ../headers 

# Directories for source files, object files, and libraries
SRCDIR := sources
OBJDIR := objects
LIBDIR := libs

# Source files for every library
SRCS_DISPLAY := $(SRCDIR)/display.c
SRCS_SERIALIZATION := $(SRCDIR)/serialization.c
# Object files for every library
OBJS_DISPLAY := $(SRCS_DISPLAY:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_SERIALIZATION := $(SRCS_SERIALIZATION:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# If STATIC is defined, we want to generate static libraries, thus we use the "ar" command and the ".a" suffix name
# Otherwise, we want to generate shared libraries, thus we use the compiler (gcc) with appropriate options (-shared -o) and the ".so" suffix name
ifdef STATIC
LIB_EXT := .a
AR := ar rs
else
LIB_EXT := .so
AR := $(CC) -shared -o
endif

# Debug mode : -g to be able to run gdb, and -DDEBUG to define the DEBUG macro in source files
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

# TEST AND SECURITY LIBRARIES
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

# Library names
DISPLAY_LIB_NAME := $(LIBDIR)/libdisplay$(LIB_EXT)
SERIALIZATION_LIB_NAME := $(LIBDIR)/libserialization$(LIB_EXT)

#############
### RULES ###
#############

.PHONY: clean

# Default target
all: ensureDirs $(DISPLAY_LIB_NAME) $(SERIALIZATION_LIB_NAME)

# Rule to make the display library
$(DISPLAY_LIB_NAME): $(OBJS_DISPLAY)
	$(AR) $@ $^ $(LDFLAGS)

# Rule to make the serialization library
$(SERIALIZATION_LIB_NAME): $(OBJS_SERIALIZATION)
	$(AR) $@ $^ $(LDFLAGS)

# Rule to create all needed directories (-p to disable errors if they already exist)
ensureDirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(LIBDIR)

# Rule to make required object files for the libraries
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Rule to clean the workspace
clean:
	-rm -r $(OBJDIR) $(LIBDIR) 2> /dev/null
