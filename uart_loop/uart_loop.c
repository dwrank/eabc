
#include <linux/module.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/platform_device.h>

/*
 * Sysfs functions
 */
u16 loopback = 0;

static ssize_t loopback_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	printk(KERN_EMERG "loopback_show\n");
      	// read loopback
	return sprintf(buf, "%s\n", loopback ? "on" : "off");
}

static ssize_t loopback_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	u16 value = 0;

	printk(KERN_EMERG "loopback_store: %s\n", buf);
	
	if (strcmp(buf, "on\n") == 0)
	{
		loopback = 1;
	}
	else if (strcmp(buf, "off\n") == 0)
	{
		loopback = 0;
	}

	return count;
}

static DEVICE_ATTR(loopback, 0644, loopback_show, loopback_store);

/* barrometer_uart2 platform device driver */
static __devinit int uart_loop_probe(struct platform_device *pdev)
{
	int err = 0;

	printk(KERN_EMERG "uart_loop_probe\n");
	
	err = device_create_file(&pdev->dev, &dev_attr_loopback);

	if (err != 0)
		printk(KERN_WARNING "fb%d: failed to register attributes ()\n",
				err);

	return err;
}

static __devexit int uart_loop_remove(struct platform_device *pdev)
{
	int err = 0;

	printk(KERN_EMERG "uart_loop_remove\n");
	
	device_remove_file(&pdev->dev, &dev_attr_loopback);

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
