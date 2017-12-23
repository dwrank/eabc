
#include <linux/module.h>
#include <linux/io.h>
#include <linux/fs.h>

static long bps_rate = 115200;

static int __init uart_loop_init(void)
{
	printk(KERN_EMERG "uart_loop_init, bps_rate=%ld\n", bps_rate);
	return 0;
}

static void __exit uart_loop_exit(void)
{
	printk(KERN_EMERG "uart_loop_exit\n");
}

MODULE_AUTHOR("Daniel Rank <drank@jetheaddev.com>");
MODULE_DESCRIPTION("uart_loop test module");
MODULE_LICENSE("GPL");
MODULE_VERSION("beta");

module_init(uart_loop_init);
module_exit(uart_loop_exit);
module_param(bps_rate, long, 0444);
