CFLAGS = -std=c99 -g -Wall
INCLUDE = -Iinclude -Ilib
#LDFLAGS =
BIN = bin/cutest
LIBRARY = lib/libcu.a

all: $(LIBRARY) $(BIN)

$(BIN): obj/main.o $(LIBRARY)
	$(CC) $^ -o $@ $(LDFLAGS)

$(LIBRARY): obj/vector.o obj/list.o
	@mkdir -p obj
	@mkdir -p lib
	@cat include/*.h >> lib/cu.h
	$(AR) rs $@ $^

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	@rm -f lib/cu.h
	@rm -f obj/*.o $(BIN) $(LIBRARY)

run: $(BIN)
	@bin/./cutest

test: $(LIBRARY)
	@cd test;
	$(MAKE)

val: $(BIN)
	@valgrind --leak-check=full bin/./cutest
