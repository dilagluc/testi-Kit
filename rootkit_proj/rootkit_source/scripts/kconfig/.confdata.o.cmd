cmd_scripts/kconfig/confdata.o := gcc -Wp,-MMD,scripts/kconfig/.confdata.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89       -I ./scripts/kconfig -c -o scripts/kconfig/confdata.o /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/confdata.c

source_scripts/kconfig/confdata.o := /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/confdata.c

deps_scripts/kconfig/confdata.o := \
    $(wildcard include/config/FOO) \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc.h \
    $(wildcard include/config/prefix) \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/expr.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/list.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc_proto.h \

scripts/kconfig/confdata.o: $(deps_scripts/kconfig/confdata.o)

$(deps_scripts/kconfig/confdata.o):
