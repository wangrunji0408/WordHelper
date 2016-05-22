SOURCES := $(wildcard *.cpp kernel/*.cpp shell/*.cpp word/*.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

CPP_FLAGS := -std=c++11 

all: main 

.PHONY: main
main: $(OBJECTS)
	g++ $(CPP_FLAGS) $(OBJECTS) -o main
	
%.o: %.cpp
	g++ $(CPP_FLAGS) -o $@ -c $<
	
.PHONY: clean
clean:
	rm *.o kernel/*.o shell/*.o word/*.o
