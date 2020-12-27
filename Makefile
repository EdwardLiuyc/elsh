CC      := c++
CCFLAGS := --std=c++11 -O3
LDFLAGS :=

all:
		mkdir -p build
		$(CC) lex/*.cc lex/*.h -I. -o build/lexer $(CCFLAGS)

clean:
		rm -rf build/*