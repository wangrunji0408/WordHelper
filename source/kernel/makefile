include ../config.make

LD_FLAG = -L../word
LD_LIB = -lword

all: libkernel$(DSO_POSTFIX)

libkernel$(DSO_POSTFIX): $(OBJECTS)
	g++ $(CPP_FLAGS) $(LD_FLAG) $(LD_LIB) -o $@ -shared $^

%.o: %.cpp
	g++ $(CPP_FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) *.o libkernel$(DSO_POSTFIX)