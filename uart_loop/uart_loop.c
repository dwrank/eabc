
#include <linux/module.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/platform_device.h>

/* barrometer_uart2 platform device driver */
static __devinit int uart_loop_probe(struct platform_device *pdev)
{
	int err = 0;

	printk(KERN_EMERG "uart_loop_probe\n");
	
	return err;
}

static __devexit int uart_loop_remove(struct platform_device *pdev)
{
	int err = 0;

	printk(KERN_EMERG "uart_loop_remove\n");
	
	return err;
}

static struct platform_driver uart_loop_driver = {
	.probe = uart_loop_probe,
	.remove = __devexit_p(uart_loop_remove),
	.driver = {
		.name = "barrometer_uart2",
		.owner = THIS_MODULE,
	},
};

/* uart_loop kernel module */
static long bps_rate = 115200;

static int __init uart_loop_init(void)
{
	printk(KERN_EMERG "uart_loop_init, bps_rate=%ld\n", bps_rate);
	return platform_driver_register(&uart_loop_driver);
}

static void __exit uart_loop_exit(void)
{
	printk(KERN_EMERG "uart_loop_exit\n");
	platform_driver_unregister(&uart_loop_driver);
}

MODULE_AUTHOR("Daniel Rank <drank@jetheaddev.com>");
MODULE_DESCRIPTION("uart_loop test module");
MODULE_LICENSE("GPL");
MODULE_VERSION("beta");

module_init(uart_loop_init);
module_exit(uart_loop_exit);
module_param(bps_rate, long, 0444);
