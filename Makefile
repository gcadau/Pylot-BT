# Pylot-BT — build one algorithm version (run from a version branch root)
#   make          -> builds ./pylot
#   make run      -> builds and runs (reads inputs from ./Dati)
#   make debug    -> AddressSanitizer build for memory-error hunting
#   make clean
CC      = gcc
CFLAGS  = -std=gnu99 -O2 -Wall -Wextra -Wno-unused-parameter
LDLIBS  = -lm
SRC     = $(wildcard *.c)
BIN     = pylot

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LDLIBS)

run: $(BIN)
	./$(BIN)

debug: $(SRC)
	$(CC) -std=gnu99 -g -O0 -fsanitize=address $(SRC) -o $(BIN)_asan $(LDLIBS)
	./$(BIN)_asan

clean:
	rm -f $(BIN) $(BIN)_asan *.o

.PHONY: run debug clean
