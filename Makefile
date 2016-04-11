TARGET=cutest
TARGET_BUILD=debug
OUTPUT_OPTION=-o $(subst src,obj,$@)
MODS=vector list option util sync
CFLAGS=-Iinclude -Ilib -Wall -Wextra -std=gnu11
LDFLAGS=-pthread lib/libcu.a
OBJ=$(addprefix obj/, $(addsuffix .o, $(MODS)))

.SUFFIXES:
.SUFFIXES: .c .o .h .a

.SECONDARY: $(OBJ)

help: debug 

ifeq ($(TARGET_BUILD), debug)
CFLAGS+=-g3
endif

ifeq ($(TARGET_BUILD), release)
CFLAGS+=-O2 -DNDEBUG
endif

all: prep lib target/$(TARGET_BUILD)/$(TARGET) 

.PHONEY: prep
prep:
	@mkdir -p obj
	@mkdir -p lib
	@mkdir -p target/$(TARGET_BUILD)
	@mkdir -p src
	@cat include/*.h | grep -Pv '^(.\*)' >> lib/cu.h


.PHONEY: debug
debug:
	@$(MAKE) TARGET_BUILD=debug all

.PHONEY: release
release:
	@$(MAKE) TARGET_BUILD=release  all

target/$(TARGET_BUILD)/$(TARGET): obj/main.o 
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONEY: lib
lib: lib/libcu.a($(OBJ))

obj/%: src/%;

clean:
	@$(RM) obj/*

clobber:
	@$(MAKE) clean
	@$(RM) -r target

