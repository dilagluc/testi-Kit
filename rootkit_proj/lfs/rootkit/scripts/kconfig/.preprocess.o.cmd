cmd_scripts/kconfig/preprocess.o := gcc -Wp,-MMD,scripts/kconfig/.preprocess.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89       -I ./scripts/kconfig -c -o scripts/kconfig/preprocess.o /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/preprocess.c

source_scripts/kconfig/preprocess.o := /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/preprocess.c

deps_scripts/kconfig/preprocess.o := \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/list.h \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/lkc.h \
    $(wildcard include/config/prefix) \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/expr.h \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/lkc_proto.h \

scripts/kconfig/preprocess.o: $(deps_scripts/kconfig/preprocess.o)

$(deps_scripts/kconfig/preprocess.o):
