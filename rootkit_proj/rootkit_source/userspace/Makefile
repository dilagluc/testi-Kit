CC=gcc
CFLAGS+=-O3 -fPIC -static
RM=rm -rf
BUILD_DIR?=$(PWD)/output

ifeq ($(wildcard ../.config),)
$(error Configuration file .config not found)
endif
include ../.config

cmd: CFLAGS+=-DZERO_WRITE=$(ZERO_WRITE) -DWRITE_ZERO=$(WRITE_ZERO)


all: cmd

cmd: build_dir
	@ echo "  CC      $(BUILD_DIR)/cmd"
	@ $(CC)  $(CFLAGS) cmd.c -o $(BUILD_DIR)/cmd
	@ strip $(BUILD_DIR)/cmd

.PHONY : clean

build_dir:
	@ mkdir -p $(BUILD_DIR)

clean:
	@ $(RM) $(BUILD_DIR)