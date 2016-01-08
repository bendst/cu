CFLAGS = -std=c99 -g -Wall
INCLUDE = -Iinclude
BIN = bin/cutest
LIBRARY = bin/libcu.a

$(BIN): obj/test.o  $(LIBRARY)
	$(CC) $^ -o $@ $(LDFLAGS)

$(LIBRARY): obj/vector.o
	$(AR) rs $@ $^

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	@rm obj/*.o $(BIN) $(LIBRARY)

run: $(BIN)
	@bin/./cutest
