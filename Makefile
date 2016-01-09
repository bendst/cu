CFLAGS = -std=c99 -g -Wall
INCLUDE = -Iinclude
BIN = bin/cutest
LIBRARY = bin/libcu.a

$(BIN): obj/test.o  $(LIBRARY)
	@mkdir -p obj
	$(CC) $^ -o $@ $(LDFLAGS)

$(LIBRARY): obj/vector.o obj/list.o
	$(AR) rs $@ $^
	@cp include/cu.h bin/

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	@rm obj/*.o $(BIN) $(LIBRARY)

run: $(BIN)
	@bin/./cutest

val: $(BIN)
	@valgrind --leak-check=full bin/./cutest
