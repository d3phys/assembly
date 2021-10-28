#
# Main project Makefile. Use it.
# 
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#

CXX = g++
CXXFLAGS = -D NDEBUG -g -std=c++14 -fmax-errors=100 -Wall -Wextra -Weffc++  \
	   -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat    \
	   -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts        \
	   -Wconditionally-supported -Wconversion -Wctor-dtor-privacy       \
	   -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
	   -Wformat-signedness -Wformat=2 -Winline -Wlogical-op             \
	   -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd          \
	   -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls  \
	   -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192       \
	   -Wstrict-null-sentinel -Wstrict-overflow=2                       \
	   -Wsuggest-attribute=noreturn -Wsuggest-final-methods             \
	   -Wsuggest-final-types -Wsuggest-override -Wswitch-default        \
	   -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code             \
	   -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix    \
	   -Wno-missing-field-initializers -Wno-narrowing                   \
	   -Wno-old-style-cast -Wno-varargs  -fcheck-new                    \
	   -fsized-deallocation -fstack-check -fstack-protector             \
	   -fstrict-overflow  -flto-odr-type-merging                        \
	   -fno-omit-frame-pointer -fPIE  -fsanitize=address                \
	   -fsanitize=bool -fsanitize=bounds  -fsanitize=enum               \
	   -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero   \
	   -fsanitize=integer-divide-by-zero  -fsanitize=leak               \
	   -fsanitize=nonnull-attribute  -fsanitize=null  -fsanitize=return \
	   -fsanitize=returns-nonnull-attribute                             \
	   -fsanitize=signed-integer-overflow -fsanitize=unreachable        \
	   -fsanitize=vla-bound -fsanitize=vptr -lm -pie 	            \
	   -Wno-format-nonliteral 

CPP = $(CXX) -E 

OBJS = 

SUBDIRS = cpu asm lib utils

INC = include

.EXPORT_ALL_VARIABLES: CXX CXXFLAGS CPP

build: $(OBJS) subdirs
	@echo build

mur: subdirs
	$(CXX) $(CXXFLAGS) -o mur utils/mur.o lib/lib.o

asm: subdirs asm/main.o
	$(CXX) $(CXXFLAGS) -o ass asm/main.o asm/asm.o lib/lib.o

cpu: subdirs cpu/main.o
	$(CXX) $(CXXFLAGS) -o ded cpu/main.o cpu/cpu.o lib/lib.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -I$(INC) $< -o $@

clean:
	rm -f *.o temp_make
	for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean); done

dep:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) dep) || exit; done

subdirs:
	for i in $(SUBDIRS); do (cd $$i && echo $$i && $(MAKE)) || exit; done

