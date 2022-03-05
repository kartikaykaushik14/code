#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/time.h>

MODULE_LICENSE("Dual BSD/GPL");

static int st_open(struct inode*, struct file*);
static int st_release(struct inode*, struct file*);
static ssize_t st_read(struct file*, char __user*, size_t, loff_t*);
ktime_t readTime, temp, year, month, date, hour, min, secs;
char *text;
int count;

static struct file_operations st_fops = {
	.open = st_open,
   	.read = st_read,
   	.release = st_release,
};

static struct miscdevice st_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "st",
	.fops = &st_fops,
};

static int st_init(void)
{
        misc_register(&st_device);
        printk(KERN_INFO "Module Loaded\n");
        return 0;
}

static void st_exit(void)
{
        misc_deregister(&st_device);
        printk(KERN_INFO "Module Unloaded\n");
}

static int st_open(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "Device Opened\n");
        return 0;
}

static int st_release(struct inode *inodep, struct file *filep) {
        printk(KERN_INFO "Device Closed\n");
        return 0;
}

static ssize_t st_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
	readTime = ktime_get_real();
	readTime = readTime/1000000000;
	year = 1970 + readTime/31557600;
	
	temp = readTime % 31556926;
	month = temp/2629800 + 1;
	
	temp = temp % 2629800;
	date = temp/86400;
	
	secs = readTime % 60;
	
	temp = readTime/60;
	min = temp%60;

	temp = temp/60;
	hour = temp%24;
		
	text = kasprintf(GFP_KERNEL, "Hello world, the current date is %lld, %lld, %lld. The current time is %lld:%lld:%lld\n", month, date, year, hour, min, secs);
	count = strlen(text);
	if (!*offset){
        	if (copy_to_user(buffer, text, count))
            		return -EFAULT;
        	printk(KERN_INFO "Epoch Time (in secs) = %lld\n", readTime);
		*offset = count;
        	return *offset;
	}

        return 0;
}

module_init(st_init);
module_exit(st_exit);
