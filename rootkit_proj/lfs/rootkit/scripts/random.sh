#!/bin/bash

function gen_random {
	RETVAL=$(cat /dev/urandom | head -c $1 | hexdump '-e"%x"')
}


gen_random 3
WRITE_ZERO=0x$RETVAL
gen_random 3
ZERO_WRITE=0x$RETVAL

cat >> $1 <<EOF

#
# Random for write_zero control
#
ZERO_WRITE=$ZERO_WRITE
WRITE_ZERO=$WRITE_ZERO

EOF
