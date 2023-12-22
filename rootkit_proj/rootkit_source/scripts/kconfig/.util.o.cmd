cmd_scripts/kconfig/util.o := gcc -Wp,-MMD,scripts/kconfig/.util.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89       -I ./scripts/kconfig -c -o scripts/kconfig/util.o /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/util.c

source_scripts/kconfig/util.o := /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/util.c

deps_scripts/kconfig/util.o := \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc.h \
    $(wildcard include/config/prefix) \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/expr.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/list.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc_proto.h \

scripts/kconfig/util.o: $(deps_scripts/kconfig/util.o)

$(deps_scripts/kconfig/util.o):
