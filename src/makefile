include config.make

LD_FLAG = -Lshell -Lkernel -Lword
LD_LIB = -lshell -lkernel -lword
TARGET := ..$(SLASH)release$(SLASH)$(OS_NAME)

all: libword libkernel libshell main copy

main: main.o
	g++ $(CPP_FLAGS) $(LD_FLAG) -o $@ $^ $(LD_LIB)

libshell:
	cd shell && make

libkernel:
	cd kernel && make

libword:
	cd word && make

copy:
	-mkdir ..$(SLASH)release
	-mkdir $(TARGET)
	$(CP) main$(EXE_POSTFIX) $(TARGET)
	$(CP) word$(SLASH)libword$(DSO_POSTFIX) $(TARGET)
	$(CP) kernel$(SLASH)libkernel$(DSO_POSTFIX) $(TARGET)
	$(CP) shell$(SLASH)libshell$(DSO_POSTFIX) $(TARGET)
	$(CP) *.txt $(TARGET)
ifeq ($(OS_NAME), Linux)
	$(CP) run_on_linux $(TARGET)
endif

%.o: %.cpp
	g++ $(CPP_FLAGS) -o $@ -c $<
	
.PHONY: clean
clean:
	$(RM) main$(EXE_POSTFIX) main.o
	cd word && make clean
	cd kernel && make clean
	cd shell && make clean
