#
# Processor module makefile 
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

OBJS = executor.o stack.o

SUBDIRS = 

INC = ../include

cpu.o: $(OBJS) subdirs main.o
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
executor.o: executor.cpp ../include/assembly.h ../include/commands \
 ../include/registers executor.h ../include/thrw.h ../include/config.h \
 stack.h ../include/actions ../include/jmp
main.o: main.cpp ../include/iomap.h executor.h ../include/thrw.h \
 ../include/config.h ../include/assembly.h ../include/commands \
 ../include/registers stack.h
stack.o: stack.cpp ../include/stack.h ../include/config.h \
 ../include/assembly.h ../include/commands ../include/registers log.h \
 ../include/hash.h
