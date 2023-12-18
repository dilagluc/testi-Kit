#ifndef FILE_H
#define FILE_H

#include "utils.h"
/*extern int nowrite;
extern int no_delete;
extern int no_open;*/

/*static inline void file_tampering(void)
{
    if (file_tampering_flag)
        file_tampering_flag = 0;
    else
        file_tampering_flag = 1;
}*/

int file_tampering_flag = 0;

static inline void file_tampering(void)
{
    //printk(KERN_DEBUG "HERE: %d bytes\n", file_tampering_flag);
    if (file_tampering_flag) {
        file_tampering_flag = 0;
        #ifdef CONFIG_NO_WRITE
            nowrite = 0;
		#endif
        #ifdef CONFIG_NO_DELETE
            no_delete = 0;
        #endif
        #ifdef CONFIG_NO_OPEN_HIDDEN
            no_open = 0;
        #endif
    }
    else {
        file_tampering_flag = 1;
    }
}

static inline void file_no_open_no_write_no_delete(void)
{
    if (nowrite == 1 && no_delete == 1 && no_open == 1) {
        #ifdef CONFIG_NO_WRITE
            nowrite = 0;
		#endif
        #ifdef CONFIG_NO_DELETE
            no_delete = 0;
        #endif
        #ifdef CONFIG_NO_OPEN_HIDDEN
            no_open = 0;
        #endif
    }
    else {
        #ifdef CONFIG_NO_WRITE
            nowrite = 1;
		#endif
        #ifdef CONFIG_NO_DELETE
            no_delete = 1;
        #endif
        #ifdef CONFIG_NO_OPEN_HIDDEN
            no_open = 1;
        #endif
    }
}

#endif
