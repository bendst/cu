CFLAGS = -std=c99 -g -Wall
INCLUDE = -Iinclude
#LDFLAGS =
BIN = bin/cutest
LIBRARY = bin/libcu.a

$(BIN): obj/main.o  $(LIBRARY)
	@mkdir -p obj
	$(CC) $^ -o $@ $(LDFLAGS)

$(LIBRARY): obj/vector.o obj/list.o
	$(AR) rs $@ $^

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	@rm obj/*.o $(BIN) $(LIBRARY)

run: $(BIN)
	@bin/./cutest

test: $(LIBRARY)
	@cd test;
	$(MAKE)

val: $(BIN)
	@valgrind --leak-check=full bin/./cutest
