# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
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
	@$(CPP) -M *.cpp -I$(INC) >> temp_make
	@cp temp_make Makefile
	@rm temp_make 
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) dep) || exit; done

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && echo $$i && $(MAKE)) || exit; done

### Dependencies ###
executor.o: executor.cpp /usr/include/stdc-predef.h /usr/include/stdio.h \
 /usr/include/bits/libc-header-start.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stddef.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdarg.h \
 /usr/include/bits/types.h /usr/include/bits/timesize.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/floatn.h \
 /usr/include/bits/floatn-common.h ../include/assembly.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdint.h \
 /usr/include/stdint.h /usr/include/bits/wchar.h \
 /usr/include/bits/stdint-intn.h /usr/include/bits/stdint-uintn.h \
 ../include/commands ../include/registers executor.h ../include/thrw.h \
 stack.h /usr/include/c++/11.1.0/stdlib.h /usr/include/c++/11.1.0/cstdlib \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/c++config.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/os_defines.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/11.1.0/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types/clock_t.h \
 /usr/include/bits/types/clockid_t.h /usr/include/bits/types/time_t.h \
 /usr/include/bits/types/timer_t.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/11.1.0/bits/std_abs.h \
 ../include/config.h
main.o: main.cpp /usr/include/stdc-predef.h
stack.o: stack.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/11.1.0/stdlib.h /usr/include/c++/11.1.0/cstdlib \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/c++config.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/bits/long-double.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/11.1.0/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/timesize.h /usr/include/bits/typesizes.h \
 /usr/include/bits/time64.h /usr/include/bits/types/clock_t.h \
 /usr/include/bits/types/clockid_t.h /usr/include/bits/types/time_t.h \
 /usr/include/bits/types/timer_t.h /usr/include/bits/stdint-intn.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/endianness.h /usr/include/bits/byteswap.h \
 /usr/include/bits/uintn-identity.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/types/sigset_t.h \
 /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/11.1.0/bits/std_abs.h \
 /usr/include/errno.h /usr/include/bits/errno.h \
 /usr/include/linux/errno.h /usr/include/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/bits/types/error_t.h /usr/include/string.h \
 /usr/include/strings.h ../include/stack.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdint.h \
 /usr/include/stdint.h /usr/include/bits/wchar.h \
 /usr/include/bits/stdint-uintn.h ../include/config.h log.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/time.h \
 /usr/include/bits/time.h /usr/include/bits/timex.h \
 /usr/include/bits/types/struct_tm.h \
 /usr/include/bits/types/struct_itimerspec.h /usr/include/assert.h \
 ../include/hash.h
