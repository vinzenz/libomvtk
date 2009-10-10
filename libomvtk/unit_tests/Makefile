CPPFLAGS+=-I../../3rdparty/tut-framework/ -I../../3rdparty/uuid/ -I../../3rdparty/uripp/src -g3 
CXXFLAGS+=-luripp -L../../3rdparty/lib

OBJECTS = \
	main.o \
	types/lldate_test.o  \
	types/lluuid_test.o \
	types/lluri_test.o \
	types/byte_sub_range_test.o \
	../libomvtk/types/lldate.o \
	../libomvtk/types/lluri.o \
	../libomvtk/types/byte_order.o \
	../libomvtk/types/lluuid.o

OBJ_o=$(foreach ob,$(OBJECTS),.obj/$(ob))

all: test

.obj/%.o : %.cpp .obj
	mkdir -p $$(dirname $@)
	$(CXX) -c $(CPPFLAGS) $< -o $@

.obj: 
	mkdir .obj

test:  $(OBJ_o)
	$(CXX) $(OBJ_o) $(CXXFLAGS) -o test

clean:  
	rm -rf .obj
	rm -f test



