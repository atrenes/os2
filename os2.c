#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/debugfs.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/pid.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("atrenes");
MODULE_DESCRIPTION("os lab2 module for debugfs interaction");
MODULE_VERSION("1.0");

static struct dentry *module_dir;
static struct dentry *module_file;
static struct device *device;

static struct file_operations fops = {
	.read = seq_read,
};

static int __init mod_init(void) {
	printk(KERN_INFO "os2 module loaded\n");
	module_dir = debugfs_create_dir("os2", NULL);
	module_file = debugfs_create_file("file", 666, module_dir, NULL, &fops);
	dev_t majmin = MKDEV(8, 0); // major and minor numbers 8 and 0 respectively
	
	return 0;
}

static void __exit mod_exit(void) {
	debugfs_remove(module_file);
	debugfs_remove(module_dir);
	printk(KERN_INFO "os2 module unloaded\n");
}

module_init(mod_init);
module_exit(mod_exit);

