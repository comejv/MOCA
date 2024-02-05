CC := gcc
CFLAGS := -Wall -Werror
ifndef STATIC
CFLAGS += -fPIC
LDFLAGS := -lm
endif
CPPFLAGS := -I headers -I ../headers 

SRCDIR := sources
OBJDIR := objects
LIBDIR := libs

# Source files
SRCS_DISPLAY := $(SRCDIR)/display.c
SRCS_SERIALIZATION := $(SRCDIR)/serialization.c
# Object files
OBJS_DISPLAY := $(SRCS_DISPLAY:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_SERIALIZATION := $(SRCS_SERIALIZATION:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Check if STATIC is defined
ifdef STATIC
LIB_EXT := .a
AR := ar rs
else
LIB_EXT := .so
AR := $(CC) -shared -o
endif

ifdef DEBUG
CFLAGS += -g 
CPPFLAGS += -DDEBUG
endif

# Library names
DISPLAY_LIB_NAME := $(LIBDIR)/libdisplay$(LIB_EXT)
SERIALIZATION_LIB_NAME := $(LIBDIR)/libserialization$(LIB_EXT)

.PHONY: clean

# Default target
all: ensureDirs $(DISPLAY_LIB_NAME) $(SERIALIZATION_LIB_NAME)

# Rule to make the display library
$(DISPLAY_LIB_NAME): $(OBJS_DISPLAY)
	$(AR) $@ $^ $(LDFLAGS)

# Rule to make the serialization library
$(SERIALIZATION_LIB_NAME): $(OBJS_SERIALIZATION)
	$(AR) $@ $^ $(LDFLAGS)

ensureDirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(LIBDIR)

# Rule to make the object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Rule to clean the workspace
clean:
	-rm -r $(OBJDIR) $(LIBDIR)