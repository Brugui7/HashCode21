EXE:=number-of-ingredients.x sol-random.x
CFLAGS:=-std=c++17

all : $(EXE)

$(EXE) : %.x : %.cpp
	g++ -o $@ $^ $(CFLAGS)

clean:
	-rm $(EXE)

.PHONY: all clean
