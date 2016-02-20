#include <linux/module.h>
#include <linux/init.h>

static int __init mon_module_init(void)
{
	printk(KERN_DEBUG "Hello WorldDriverThiery !\n");
	return 0;
}

static void __exit mon_module_cleanup(void)
{
    printk(KERN_DEBUG "Goodbye World You!\n");
}

module_init(mon_module_init);
module_exit(mon_module_cleanup);
