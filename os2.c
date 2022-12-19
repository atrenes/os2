#include <linux/device/class.h>
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
#include <linux/of.h>
#include <linux/sched.h>
#include <linux/types.h>

#define BUFFER_SIZE 128

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("atrenes");
MODULE_DESCRIPTION("os lab2 module for debugfs interaction");
MODULE_VERSION("1.0");

static struct dentry *module_dir;
static struct dentry *module_file;
static struct pci_dev *pci_device = NULL;
static void print_device(struct seq_file *file, struct pci_dev *pci_device);
static int print_struct(struct seq_file *file, void *data);

static ssize_t write_structures(struct file *file, const char __user *buffer, size_t length, loff_t *ptr_offset) {
	printk(KERN_INFO "get arguments\n");
	char user_data[BUFFER_SIZE];
	int pid;
	unsigned int vendor_id, device_id;
	copy_from_user(user_data, buffer, length);
	sscanf(user_data, "vendor_id: %x, device_id: %x", &vendor_id, &device_id);
	pci_device = pci_get_device(vendor_id, device_id, NULL);
	single_open(file, print_struct, NULL);
	return strlen(user_data);
}

static int print_struct(struct seq_file *file, void *data) {
    print_device(file, pci_device);
    return 0;
}

static void print_device(struct seq_file *file, struct pci_dev *pci_device) {
    if (pci_device == NULL) {
        seq_printf(file, "Can't find pci_device with this params\n");
    } else {
        seq_printf(file, "pci_device structure: {\n");
        seq_printf(file, "  vendor_ID: %u,\n", pci_device->vendor);
        seq_printf(file, "  device_ID: %u,\n", pci_device->device);
        seq_printf(file, "  init name: %s%,\n", pci_device->dev.init_name);
        seq_printf(file, "  class name: %s,\n", pci_device->dev.class->name);
        seq_printf(file, "}\n");
    }
}


static struct file_operations fops = {
	.read = seq_read,
	.write = write_structures
};

static int __init mod_init(void) {
	printk(KERN_INFO "os2 module loaded\n");
	module_dir = debugfs_create_dir("os2", NULL);
	module_file = debugfs_create_file("file", 666, module_dir, NULL, &fops);
	
	//dev_t _devt = MKDEV(13, 32); // major and minor numbers 13 and 32 respectively (mouse0?)
	/*
	node = of_node_get(NULL);
	node = of_root;
	printk(KERN_INFO "%s", node->name);
	
	pochemy ono ne rabotaet ya tak bolshe ne mogy
	*/
	
	return 0;
}

static void __exit mod_exit(void) {
	debugfs_remove(module_file);
	debugfs_remove(module_dir);
	printk(KERN_INFO "os2 module unloaded\n");
}

module_init(mod_init);
module_exit(mod_exit);

