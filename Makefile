BIN = run

all:
	gcc -o $(BIN) *.c

clean:
	rm -f $(BIN) *.o
