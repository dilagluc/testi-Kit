cmd_scripts/basic/fixdep := gcc -Wp,-MMD,scripts/basic/.fixdep.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89       -I ./scripts/basic   -o scripts/basic/fixdep /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/basic/fixdep.c   

source_scripts/basic/fixdep := /home/parrot/Documents/testi/rootkit_proj/rootkit_source/scripts/scripts/basic/fixdep.c

deps_scripts/basic/fixdep := \
    $(wildcard include/config/HIS_DRIVER) \
    $(wildcard include/config/MY_OPTION) \
    $(wildcard include/config/FOO) \

scripts/basic/fixdep: $(deps_scripts/basic/fixdep)

$(deps_scripts/basic/fixdep):
