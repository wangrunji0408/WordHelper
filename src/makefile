OS_NAME = $(shell uname)

ifeq ($(OS_NAME), Linux)
	# Linux
	DSO_POSTFIX = .so
	LS = ls
	RM = rm
	SLASH = /
else

ifeq ($(OS_NAME), Darwin)
	# Mac
	DSO_POSTFIX = .dylib
	LS = ls
	RM = rm
	SLASH = /
else
	# Windows
	OS_NAME = Windows
	DSO_POSTFIX = .dll
	LS = dir /b
	RM = del
	SLASH = \\
endif

endif

CPP_FLAGS := -std=c++11 -fPIC 

WORD_SRC := $(shell $(LS) word$(SLASH)*.cpp)
WORD_OBJ := $(patsubst %.cpp, %.o, $(WORD_SRC))
KERNEL_SRC := $(shell $(LS) kernel$(SLASH)*.cpp)
KERNEL_OBJ := $(patsubst %.cpp, %.o, $(KERNEL_SRC))
SHELL_SRC := $(shell $(LS) shell$(SLASH)*.cpp)
SHELL_OBJ := $(patsubst %.cpp, %.o, $(SHELL_SRC))

LIB_WORD := word$(SLASH)libword$(DSO_POSTFIX)
LIB_KERNEL := kernel$(SLASH)libkernel$(DSO_POSTFIX)
LIB_SHELL := shell$(SLASH)libshell$(DSO_POSTFIX)
LIB := $(LIB_WORD) $(LIB_KERNEL) $(LIB_SHELL)

all: main 

main: main.o $(LIB)
	g++ $(CPP_FLAGS) -o $@ $^

$(LIB_SHELL): $(SHELL_OBJ) $(LIB_KERNEL) $(LIB_WORD)
	g++ $(CPP_FLAGS) -o $@ -shared $^

$(LIB_KERNEL): $(KERNEL_OBJ) $(LIB_WORD) 
	g++ $(CPP_FLAGS) -o $@ -shared $^

$(LIB_WORD): $(WORD_OBJ)
	g++ $(CPP_FLAGS) -o $@ -shared $^ 

%.o: %.cpp
	g++ $(CPP_FLAGS) -o $@ -c $<
	
.PHONY: clean
clean:
	$(RM) $(shell $(LS) *.o kernel$(SLASH)*.o shell$(SLASH)*.o word$(SLASH)*.o) $(LIB)
