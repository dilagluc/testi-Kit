cmd_scripts/kconfig/mconf.o := gcc -Wp,-MMD,scripts/kconfig/.mconf.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89      -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -I ./scripts/kconfig -c -o scripts/kconfig/mconf.o /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/mconf.c

source_scripts/kconfig/mconf.o := /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/mconf.c

deps_scripts/kconfig/mconf.o := \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc.h \
    $(wildcard include/config/prefix) \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/expr.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/list.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lkc_proto.h \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lxdialog/dialog.h \

scripts/kconfig/mconf.o: $(deps_scripts/kconfig/mconf.o)

$(deps_scripts/kconfig/mconf.o):
