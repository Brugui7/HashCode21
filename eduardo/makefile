EXE:=sol-naive.x sol-2.x sol-3E.x sol-simulation.x
SRC:=$(EXE:.x=.cpp)
CFLAGS:=-std=c++17

all : $(EXE)

$(EXE) : %.x : %.cpp
	g++ -o $@ $^ $(CFLAGS)

clean:
	-rm $(EXE)
    
format:
	-clang-format -i $(SRC)

.PHONY: all clean format
