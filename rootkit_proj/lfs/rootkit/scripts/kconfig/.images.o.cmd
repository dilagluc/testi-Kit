cmd_scripts/kconfig/images.o := gcc -Wp,-MMD,scripts/kconfig/.images.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89       -I ./scripts/kconfig -c -o scripts/kconfig/images.o /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/images.c

source_scripts/kconfig/images.o := /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/images.c

deps_scripts/kconfig/images.o := \
  /home/parrot/Documents/testi/disk_image/bdss/scripts/scripts/kconfig/images.h \

scripts/kconfig/images.o: $(deps_scripts/kconfig/images.o)

$(deps_scripts/kconfig/images.o):
