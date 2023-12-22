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
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x5f203a5c, "module_layout" },
	{ 0x63026490, "unregister_kprobe" },
	{ 0xfcca5424, "register_kprobe" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x670ecece, "__x86_indirect_thunk_rbx" },
	{ 0x6383b27c, "__x86_indirect_thunk_rdx" },
	{ 0x8c17efd, "vm_mmap" },
	{ 0x7f93b404, "param_ops_long" },
	{ 0x5b56860c, "vm_munmap" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C9627B0C83FA2B2344574BC");
