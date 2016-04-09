CFLAGS = -std=c11 -g -Wall 
LDFLAGS = -Llib -lcu
INCLUDE = -Iinclude -Ilib
BIN = bin/cutest
LIBRARY = lib/libcu.a
CC = clang
OBJ = obj/vector.o obj/list.o obj/option.o obj/util.o obj/sync.o
all: FOLDER $(LIBRARY) $(BIN)

FOLDER:
	@mkdir -p bin
	@mkdir -p obj
	@mkdir -p lib

$(BIN): obj/main.o
	$(CC) -pthread $^ -o $@ $(LDFLAGS)

$(LIBRARY): $(OBJ) 
	@cat include/*.h | grep -Pv '^(.\*)' >> lib/cu.h
	$(AR) rsv $@ $^

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf lib bin obj

run: $(BIN)
	@bin/./cutest

test: $(LIBRARY)
	@cd test;
	$(MAKE)

val: $(BIN)
	@valgrind --leak-check=full bin/./cutest
