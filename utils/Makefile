#
# Utilities makefile.
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

OBJS = mur.o

INC = ../include

make: $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -I$(INC) $< -o $@

clean:
	rm -f *.o temp_make

dep:
	@sed '/\#\#\# Dependencies \#\#\#/q' < Makefile > temp_make
	@$(CPP) -MM *.cpp -I$(INC) >> temp_make
	@cp temp_make Makefile
	@rm temp_make


### Dependencies ###
mur.o: mur.cpp ../include/hash.h ../include/assembly.h \
 ../include/commands ../include/registers
