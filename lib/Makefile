#
# Makefile for some libs needed.
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

OBJS = hash.o iomap.o

INC = ../include

lib.o: $(OBJS)
	$(LD) -r -o $@ $(OBJS)

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
hash.o: hash.cpp ../include/hash.h
iomap.o: iomap.cpp ../include/iomap.h ../include/thrw.h \
 ../include/config.h ../include/assembly.h ../include/commands \
 ../include/registers
