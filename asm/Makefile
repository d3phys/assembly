# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...

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
	@$(CPP) -M *.cpp -I$(INC) >> temp_make
	@cp temp_make Makefile
	@rm temp_make
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) dep) || exit; done

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && echo $$i && $(MAKE)) || exit; done

### Dependencies ###
compiler.o: compiler.cpp /usr/include/stdc-predef.h /usr/include/assert.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/bits/long-double.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h \
 /usr/include/errno.h /usr/include/bits/errno.h \
 /usr/include/linux/errno.h /usr/include/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/bits/types/error_t.h /usr/include/string.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stddef.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/strings.h /usr/include/c++/11.1.0/stdlib.h \
 /usr/include/c++/11.1.0/cstdlib \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/c++config.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/os_defines.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/11.1.0/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
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
 ../include/assembly.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdint.h \
 /usr/include/stdint.h /usr/include/bits/wchar.h \
 /usr/include/bits/stdint-uintn.h ../include/commands \
 ../include/registers ../include/thrw.h /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h ../include/hash.h parse.h compiler.h
main.o: main.cpp /usr/include/stdc-predef.h /usr/include/stdio.h \
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
 /usr/include/bits/floatn-common.h /usr/include/string.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/strings.h /usr/include/c++/11.1.0/stdlib.h \
 /usr/include/c++/11.1.0/cstdlib \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/c++config.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/os_defines.h \
 /usr/include/c++/11.1.0/x86_64-pc-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/11.1.0/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/bits/types/clock_t.h \
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
 /usr/include/assert.h compiler.h parse.h ../include/assembly.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdint.h \
 /usr/include/stdint.h /usr/include/bits/wchar.h \
 /usr/include/bits/stdint-uintn.h ../include/commands \
 ../include/registers ../include/thrw.h /usr/include/sys/mman.h \
 /usr/include/bits/mman.h /usr/include/bits/mman-map-flags-generic.h \
 /usr/include/bits/mman-linux.h /usr/include/bits/mman-shared.h \
 /usr/include/errno.h /usr/include/bits/errno.h \
 /usr/include/linux/errno.h /usr/include/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/bits/types/error_t.h /usr/include/fcntl.h \
 /usr/include/bits/fcntl.h /usr/include/bits/fcntl-linux.h \
 /usr/include/bits/types/struct_iovec.h /usr/include/linux/falloc.h \
 /usr/include/bits/stat.h /usr/include/bits/struct_stat.h \
 /usr/include/sys/stat.h /usr/include/bits/statx.h \
 /usr/include/linux/stat.h /usr/include/linux/types.h \
 /usr/include/asm/types.h /usr/include/asm-generic/types.h \
 /usr/include/asm-generic/int-ll64.h /usr/include/asm/bitsperlong.h \
 /usr/include/asm-generic/bitsperlong.h /usr/include/linux/posix_types.h \
 /usr/include/linux/stddef.h /usr/include/asm/posix_types.h \
 /usr/include/asm/posix_types_64.h /usr/include/asm-generic/posix_types.h \
 /usr/include/bits/statx-generic.h \
 /usr/include/bits/types/struct_statx_timestamp.h \
 /usr/include/bits/types/struct_statx.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/bits/getopt_posix.h \
 /usr/include/bits/getopt_core.h /usr/include/bits/unistd_ext.h \
 ../include/iomap.h
notation.o: notation.cpp /usr/include/stdc-predef.h \
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
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/assert.h /usr/include/errno.h \
 /usr/include/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/asm/errno.h /usr/include/asm-generic/errno.h \
 /usr/include/asm-generic/errno-base.h /usr/include/bits/types/error_t.h \
 ../include/thrw.h parse.h
parse.o: parse.cpp /usr/include/stdc-predef.h /usr/include/assert.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/bits/long-double.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h \
 /usr/include/string.h /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include/stddef.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/strings.h parse.h
