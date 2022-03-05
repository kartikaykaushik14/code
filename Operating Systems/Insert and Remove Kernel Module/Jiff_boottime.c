#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

unsigned long initJiffy, exitJiffy, jiffyDiff;
ktime_t initTimer, exitTimer, timerDiff;

static int hello_init(void)
{
	printk(KERN_ALERT "Hello, world\n");
	initJiffy = jiffies;			// Get initial tick time (in secs) while inserting the module into Kernel
	initTimer = ktime_get_boottime();	// Get timer reading while inserting the module into Kernel
	
	printk(KERN_ALERT "Initial tick time (in msecs) = %lu\n", initJiffy * 1000 / HZ);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
	exitJiffy = jiffies;			// Get final tick time (in secs) while removing the module from Kernel
	exitTimer = ktime_get_boottime();	// Get timer reading while removing the module into Kernel

	jiffyDiff = (exitJiffy - initJiffy) * 1000 / HZ; // Get diff in the value of jiffies from inserting to removing the module
	timerDiff = (exitTimer - initTimer) / 1000000;	 // Get diff in the value of timer readings from inserting to removing the module
	
	printk(KERN_ALERT "Time between insertion and removal of module -\n");
	printk(KERN_ALERT "Using difference in value of jiffies = %lu\n", jiffyDiff);
	printk(KERN_ALERT "Using time difference obtained by reading the timer = %llu\n", timerDiff);
}

module_init(hello_init);
module_exit(hello_exit);
