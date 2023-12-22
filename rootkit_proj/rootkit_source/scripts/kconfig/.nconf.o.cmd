cmd_scripts/kconfig/nconf.o := gcc -Wp,-MMD,scripts/kconfig/.nconf.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89      -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -I ./scripts/kconfig -c -o scripts/kconfig/nconf.o /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/nconf.c

source_scripts/kconfig/nconf.o := /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/nconf.c

deps_scripts/kconfig/nconf.o := \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/lkc.h \
    $(wildcard include/config/prefix) \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/expr.h \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/list.h \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/lkc_proto.h \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/nconf.h \

scripts/kconfig/nconf.o: $(deps_scripts/kconfig/nconf.o)

$(deps_scripts/kconfig/nconf.o):
