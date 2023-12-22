#ifdef CONFIG_NO_DELETE
#include "utils.h"

int (*orig_do_unlinkat)(int dfd, struct filename *name);

int rk_do_unlinkat(int dfd, struct filename *name) {
    const char* prefix[] = CONFIG_RK_NO_DELETE_FILE_PREFIX;

    int ret = -ENAMETOOLONG;
    int i = 0;
    int size = sizeof(prefix) / sizeof(prefix[0]);
    for (i = 0; i < size  && strstr(name->name, prefix[i]) == NULL ; ++i);

	if (i == size && no_delete == 0)
		ret = orig_do_unlinkat(dfd, name);
	return ret;
}

#endif