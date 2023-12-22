cmd_scripts/kconfig/menu.o := gcc -Wp,-MMD,scripts/kconfig/.menu.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89       -I ./scripts/kconfig -c -o scripts/kconfig/menu.o /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/menu.c

source_scripts/kconfig/menu.o := /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/menu.c

deps_scripts/kconfig/menu.o := \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc.h \
    $(wildcard include/config/prefix) \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/expr.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/list.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc_proto.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/internal.h \

scripts/kconfig/menu.o: $(deps_scripts/kconfig/menu.o)

$(deps_scripts/kconfig/menu.o):
