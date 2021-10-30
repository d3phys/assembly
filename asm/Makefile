#
# Assembler module makefile
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

OBJS = compiler.o parse.o notation.o

SUBDIRS =

INC = ../include

asm.o: $(OBJS) subdirs
	$(LD) -r -o $@ $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -I$(INC) $< -o $@

clean:
	rm -f *.o temp_make
	for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean); done

dep:
	@sed '/\#\#\# Dependencies \#\#\#/q' < Makefile > temp_make
	@$(CPP) -MM *.cpp -I$(INC) >> temp_make
	@cp temp_make Makefile
	@rm temp_make
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) dep) || exit; done

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && echo $$i && $(MAKE)) || exit; done

### Dependencies ###
compiler.o: compiler.cpp ../include/assembly.h ../include/commands \
 ../include/registers ../include/thrw.h ../include/hash.h parse.h \
 compiler.h
main.o: main.cpp compiler.h parse.h ../include/assembly.h \
 ../include/commands ../include/registers ../include/thrw.h \
 ../include/iomap.h
notation.o: notation.cpp ../include/thrw.h parse.h
parse.o: parse.cpp parse.h
