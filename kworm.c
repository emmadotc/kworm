#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/uaccess.h>

#define NAME "worm"

MODULE_DESCRIPTION("worm");
MODULE_LICENSE("BSD-3-Clause");
MODULE_VERSION("1.0");

int worm_phase = 0;
static int major;

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release
};

static int __init kworm_init(void)
{
    major = register_chrdev(0, NAME, &fops);

    if(major < 0)
    {
        printk(KERN_ALERT "kworm init failed\n");
        return major;
    }

    printk(KERN_INFO "kworm init (%d)\n", major);
    return 0;
}

static void __exit kworm_exit(void)
{
    unregister_chrdev(major, NAME);
    printk(KERN_INFO "kworm exit\n");
}

static int dev_open(struct inode* inodep, struct file* filep)
{
    printk(KERN_INFO "kworm opened\n");
    return 0;
}


static ssize_t dev_write(struct file* filep, const char* buffer, size_t len, loff_t* offset)
{
    printk(KERN_INFO "kworm read-only\n");
    return -EFAULT;
}

static int dev_release(struct inode* inodep, struct file* filep)
{
    printk(KERN_INFO "kworm closed\n");
    return 0;
}

static ssize_t dev_read(struct file* filep, char* buffer, size_t len, loff_t* offset)
{
    int errors = 0;
    char *worm = "|\r(\r|\r)\r";
    int worm_len = 2;
    worm_phase = (worm_phase % 4) + 1;

    mdelay(100);

    errors = copy_to_user(buffer, worm + ((worm_phase - 1) * 2), worm_len);

    return errors == 0 ? worm_len : -EFAULT;
}

module_init(kworm_init);
module_exit(kworm_exit);

