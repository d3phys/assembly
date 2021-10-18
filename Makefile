# Created by d3phys
# 16.10.2021

SUBDIRS := 
SOURCE  := $(wildcard *.cpp)
BINARY  := binary

ifeq ($(MAKELEVEL), 0)
BUILD_DIR := build
BUILD 	  := $(BUILD_DIR)
export BUILD
else
BUILD_DIR := $(shell printf '../%.0s' {1..${MAKELEVEL}})$(BUILD)
endif

OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCE))

make: mkdir dependences $(OBJECTS) 
	@for dir in $(SUBDIRS); do  \
		$(MAKE) -C $$dir ;  \
	done
ifeq ($(MAKELEVEL), 0)
	$(CXX) -o $(BUILD_DIR)/$(BINARY) $(wildcard $(BUILD_DIR)/*.o)
endif

mkdir:
ifeq ($(MAKELEVEL), 0)
	@mkdir -p $(BUILD_DIR)
endif

$(BUILD_DIR)/%.o: %.cpp 
	    $(CXX) -c -o $@ $<

.PHONY: clean
clean:
	rm -R -f ./build

dependences: $(SOURCE)


