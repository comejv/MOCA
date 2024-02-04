CC=gcc
CFLAGS=-Wall -Werror
ifndef STATIC
CFLAGS+=-fPIC
endif
CPPFLAGS=-I display_lib/headers -I serialization_lib/headers -I ../headers 
LDFLAGS=-lm

# répertoires de la librairie display
SRCDIR_DISPLAY=display_lib/sources
HEADERSDIR_DISPLAY=display_lib/headers
OBJDIR_DISPLAY=display_lib/objects
LIBDIR_DISPLAY=display_lib/lib

# répertoires de la librairie serialization
SRCDIR_SERIALIZATION=serialization_lib/sources
HEADERSDIR_SERIALIZATION=serialization_lib/headers
OBJDIR_SERIALIZATION=serialization_lib/objects
LIBDIR_SERIALIZATION=serialization_lib/lib

# fichiers de la librairie display
SRCS_DISPLAY=$(wildcard $(SRCDIR_DISPLAY)/*.c)
HEADERS_DISPLAY=$(wildcard $(HEADERSDIR_DISPLAY)/*.h)
OBJS_DISPLAY=$(SRCS_DISPLAY:$(SRCDIR_DISPLAY)/%.c=$(OBJDIR_DISPLAY)/%.o)
ifdef STATIC
LIB_DISPLAY=$(LIBDIR_DISPLAY)/libdisplay.a
else
LIB_DISPLAY=$(LIBDIR_DISPLAY)/libdisplay.so
endif

# fichiers de la librairie serialization
SRCS_SERIALIZATION=$(wildcard $(SRCDIR_SERIALIZATION)/*.c)
HEADERS_SERIALIZATION=$(wildcard $(HEADERSDIR_SERIALIZATION)/*.h)
OBJS_SERIALIZATION=$(SRCS_SERIALIZATION:$(SRCDIR_SERIALIZATION)/%.c=$(OBJDIR_SERIALIZATION)/%.o)
ifdef STATIC 
LIB_SERIALIZATION=$(LIBDIR_SERIALIZATION)/libserialization.a
else
LIB_SERIALIZATION=$(LIBDIR_SERIALIZATION)/libserialization.so
endif

# librairies à générer
LIBS=$(LIB_DISPLAY) $(LIB_SERIALIZATION)

.PHONY : clean

all : $(LIBS) 

$(OBJDIR_DISPLAY)/%.o : $(SRCDIR_DISPLAY)/%.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR_SERIALIZATION)/%.o : $(SRCDIR_SERIALIZATION)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR_DISPLAY)/display.o : $(HEADERSDIR_DISPLAY)/display.h ../headers/structures.h
$(OBJDIR_SERIALIZATION)/serialization.o : $(HEADERSDIR_SERIALIZATION)/serialization.h ../headers/structures.h ../headers/word_tools.h

# librarie display
$(LIB_DISPLAY) : $(OBJS_DISPLAY)
ifdef STATIC
	ar rs $@ $(OBJS_DISPLAY)
else
	$(CC) -shared $(OBJS_DISPLAY) -o $@ $(LDFLAGS)
endif

# librairie serialization
$(LIB_SERIALIZATION) : $(OBJS_SERIALIZATION)
ifdef STATIC 
	ar rs $@ $(OBJS_SERIALIZATION) 
else
	$(CC) -shared $(OBJS_SERIALIZATION) -o $@ $(LDFLAGS)
endif

clean : 
	@echo "Nettoyage des fichiers objets et des librairies"
	-rm -r $(OBJDIR_DISPLAY)/*.o $(OBJDIR_SERIALIZATION)/*.o $(LIBDIR_DISPLAY)/* $(LIBDIR_SERIALIZATION)/*