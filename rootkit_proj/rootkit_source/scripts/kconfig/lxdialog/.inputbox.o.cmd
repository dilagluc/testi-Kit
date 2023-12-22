cmd_scripts/kconfig/lxdialog/inputbox.o := gcc -Wp,-MMD,scripts/kconfig/lxdialog/.inputbox.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89      -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -I ./scripts/kconfig -c -o scripts/kconfig/lxdialog/inputbox.o /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lxdialog/inputbox.c

source_scripts/kconfig/lxdialog/inputbox.o := /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lxdialog/inputbox.c

deps_scripts/kconfig/lxdialog/inputbox.o := \
  /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/kconfig/lxdialog/dialog.h \

scripts/kconfig/lxdialog/inputbox.o: $(deps_scripts/kconfig/lxdialog/inputbox.o)

$(deps_scripts/kconfig/lxdialog/inputbox.o):
