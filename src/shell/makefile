include ../config.make

LD_FLAG = -L../word -L../kernel
LD_LIB = -lword -lkernel

all: libshell$(DSO_POSTFIX)

libshell$(DSO_POSTFIX): $(OBJECTS)
	g++ $(CPP_FLAGS) $(LD_FLAG) $(LD_LIB) -o $@ -shared $^

%.o: %.cpp
	g++ $(CPP_FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) *.o libshell$(DSO_POSTFIX)