LS = ls
RM = rm -f
CP = cp
SLASH = /
EXE_POSTFIX = 

ifeq ($(OS_NAME), )
OS_NAME = $(shell uname)

ifeq ($(OS_NAME), Linux)
	# Linux
	DSO_POSTFIX = .so
else
ifeq ($(OS_NAME), Darwin)
	# Mac
	DSO_POSTFIX = .dylib
else
	# Windows
	OS_NAME = Windows
	DSO_POSTFIX = .dll
	EXE_POSTFIX = .exe
	LS = dir /b
	RM = del /f
	CP = copy
	SLASH = \\
endif
endif
endif

SOURCES := $(shell $(LS) *.cpp)
HEADERS := $(shell $(LS) *.h)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))
CPP_FLAGS := -std=c++11 -fPIC 