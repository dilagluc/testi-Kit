#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x5f203a5c, "module_layout" },
	{ 0x466f7d3b, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0xac15f01f, "put_pid" },
	{ 0x7410aba2, "strreplace" },
	{ 0x754d539c, "strlen" },
	{ 0x3854774b, "kstrtoll" },
	{ 0x447f39a4, "prepare_kernel_cred" },
	{ 0x63026490, "unregister_kprobe" },
	{ 0x66e25167, "commit_creds" },
	{ 0xe0b13336, "argv_free" },
	{ 0xfcca5424, "register_kprobe" },
	{ 0x2d5f69b3, "rcu_read_unlock_strict" },
	{ 0x75b1a0c8, "kobject_del" },
	{ 0x8522d6bc, "strncpy_from_user" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x95ce7032, "kobject_create_and_add" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x8100c98e, "current_task" },
	{ 0x5a921311, "strncmp" },
	{ 0x1e6d26a8, "strstr" },
	{ 0xa7eedcc4, "call_usermodehelper" },
	{ 0xa5a1793e, "unregister_ftrace_function" },
	{ 0x8c8569cb, "kstrtoint" },
	{ 0x6f935e35, "ftrace_set_filter_ip" },
	{ 0x9544b51e, "init_task" },
	{ 0x296695f, "refcount_warn_saturate" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x92997ed8, "_printk" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x1027ced7, "kmem_cache_alloc_trace" },
	{ 0x9ec01f6b, "find_get_pid" },
	{ 0x37a0cba, "kfree" },
	{ 0x90de72a9, "register_ftrace_function" },
	{ 0xb3418b8, "__put_task_struct" },
	{ 0x7380dffa, "argv_split" },
	{ 0x58962b9c, "get_pid_task" },
	{ 0xb0e602eb, "memmove" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "CB61066B01277DFEC29DF60");
