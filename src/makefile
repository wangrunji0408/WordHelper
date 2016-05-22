SOURCES := $(wildcard *.cpp kernel/*.cpp shell/*.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

DSO_POSTFIX := .dylib

CPP_FLAGS := -std=c++11 

all: main 

.PHONY: main
main: $(OBJECTS) libword$(DSO_POSTFIX)
	g++ $(CPP_FLAGS) $(OBJECTS) libword$(DSO_POSTFIX) -o main

WORD_SRC := $(wildcard word/*.cpp)
WORD_OBJ := $(patsubst %.cpp, %.o, $(WORD_SRC))

libword$(DSO_POSTFIX): $(WORD_OBJ)
	g++ $(CPP_FLAGS) $(WORD_OBJ) -fPIC -shared -o libword$(DSO_POSTFIX)

%.o: %.cpp
	g++ $(CPP_FLAGS) -o $@ -c $<
	
.PHONY: clean
clean:
	rm *.o kernel/*.o shell/*.o word/*.o *$(DSO_POSTFIX)
