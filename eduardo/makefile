EXE:=sol-naive.x sol-2.x sol-3E.x
CFLAGS:=-std=c++17

all : $(EXE)

$(EXE) : %.x : %.cpp
	g++ -o $@ $^ $(CFLAGS)

clean:
	-rm $(EXE)

.PHONY: all clean
