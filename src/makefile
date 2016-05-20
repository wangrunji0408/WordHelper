KERNELS = kernel/*.cpp
SHELLS = shell/*.cpp
WORDS = word/*.cpp
TARGET = $(KERNELS) $(SHELLS) $(WORDS) main.cpp

all: main

main: $(TARGET)
	g++ $(TARGET) -o main -std=c++11