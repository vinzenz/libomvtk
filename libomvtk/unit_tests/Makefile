CPPFLAGS=-I../../3rdparty/tut-framework/
CXXFLAGS=
LDFLAGS=

OBJECTS = main.o types/lldate_test.o

OBJ_o=$(foreach ob,$(OBJECTS),.obj/$(ob))

all: test



.obj/%.o : %.cpp .obj
	mkdir -p $$(dirname $@)
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.obj: 
	mkdir .obj

test:  $(OBJ_o)
	$(CXX) $(OBJ_o) $(CXXFLAGS) -o test

clean:  
	rm -rf .obj
	rm -f test



