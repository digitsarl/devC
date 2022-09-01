FACT_GENERATOR = executable/Main
CC = clang
CFLAGS= 
LINKER = clang
LFLAGS = -lm

SRCDIR = src
OBJDIR = obj
FACT_GENERATOR_CFLAGS = $(CFLAGS) -I serd/include -I sord/include -I sord/src

PARSER_SRCDIR = serd/src
PARSER_OBJDIR = serd/obj

TSTORE_SRCDIR = sord/src
TSTORE_OBJDIR = sord/obj

ZIX_SRCDIR = sord/src/zix
ZIX_OBJDIR = sord/obj/zix

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PARSER_MAIN := serdi.c
PARSER_SOURCES := $(filter-out $(PARSER_SRCDIR)/$(PARSER_MAIN),$(wildcard $(PARSER_SRCDIR)/*.c))
PARSER_INCLUDES := $(wildcard $(PARSER_SRCDIR)/*.h)
PARSER_OBJECTS := $(PARSER_SOURCES:$(PARSER_SRCDIR)/%.c=$(PARSER_OBJDIR)/%.o)
PARSER_CFLAGS = $(CFLAGS) -I serd/include

TSTORE_MAIN := $(TSTORE_SRCDIR)/sordi.c $(TSTORE_SRCDIR)/sordmm_test.cpp $(TSTORE_SRCDIR)/sord_test.c $(TSTORE_SRCDIR)/sord_validate.c
TSTORE_SOURCES := $(filter-out $(TSTORE_MAIN),$(wildcard $(TSTORE_SRCDIR)/*.c))
TSTORE_INCLUDES := $(wildcard $(TSTORE_SRCDIR)/*.h)
TSTORE_OBJECTS := $(TSTORE_SOURCES:$(TSTORE_SRCDIR)/%.c=$(TSTORE_OBJDIR)/%.o)
TSTORE_CFLAGS = $(CFLAGS) -I sord/include/ -I serd/include/ -I sord/src/

ZIX_SOURCES := $(wildcard $(ZIX_SRCDIR)/*.c)
ZIX_INCLUDES := $(wildcard $(ZIX_SRCDIR)/*.h)
ZIX_OBJ := $(ZIX_SOURCES:$(ZIX_SRCDIR)/%.c=$(ZIX_OBJDIR)/%.o)
ZIX_CFLAGS = -I sord/src/

RM = rm -rf
MKDIR = mkdir

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES) | objects
	@$(CC) $(FACT_GENERATOR_CFLAGS)  -c $< -o $@

$(PARSER_OBJECTS): $(PARSER_OBJDIR)/%.o : $(PARSER_SRCDIR)/%.c $(PARSER_INCLUDES) | parser_objects
	@$(CC) $(PARSER_CFLAGS) -c $< -o $@

$(TSTORE_OBJECTS): $(TSTORE_OBJDIR)/%.o : $(TSTORE_SRCDIR)/%.c $(TSTORE_INCLUDES) | tstore_objects
	@$(CC) $(TSTORE_CFLAGS) -c $< -o $@

$(ZIX_OBJ): $(ZIX_OBJDIR)/%.o : $(ZIX_SRCDIR)/%.c $(ZIX_INCLUDES) | zix_objects
	@$(CC) $(ZIX_CFLAGS) -c $< -o $@

objects:
	@$(MKDIR) $(OBJDIR)

parser_objects:
	@$(MKDIR) $(PARSER_OBJDIR)

tstore_objects:
	@$(MKDIR) $(TSTORE_OBJDIR)

zix_objects:
	@$(MKDIR) $(ZIX_OBJDIR)

.PHONY: clean all

$(FACT_GENERATOR): $(OBJECTS) $(PARSER_OBJECTS) $(TSTORE_OBJECTS)
	$(CC) -o $@ $^ $(FACT_GENERATOR_CFLAGS) $(LFLAGS)

clean:
	@$(RM) $(OBJDIR) $(PARSER_OBJDIR) $(TSTORE_OBJDIR)

all : clean $(FACT_GENERATOR)

.DEFAULT_GOAL := all
