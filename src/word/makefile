include ../config.make

LD_FLAG = 
LD_LIB = 

all: libword$(DSO_POSTFIX)

libword$(DSO_POSTFIX): $(OBJECTS)
	g++ $(CPP_FLAGS) $(LD_FLAG) $(LD_LIB) -o $@ -shared $^

%.o: %.cpp
	g++ $(CPP_FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) *.o libword$(DSO_POSTFIX)