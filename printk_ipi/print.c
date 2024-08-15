#include <linux/delay.h>
#include <linux/cpumask.h>
#include <linux/smp.h>
#include <linux/kthread.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static void ipi_printk(void *info)
{
	printk("Hello from CPU %d\n", smp_processor_id());
}

void trigger_ipi_printk(void)
{
	on_each_cpu(ipi_printk, NULL, false);
}

static int __init print_init(void)
{
	trigger_ipi_printk();
	return 0;
}

static void __exit print_exit(void)
{
	printk("alan: exit");
}

module_init(print_init);
module_exit(print_exit);
MODULE_INFO(intree, "Y");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan Song");
MODULE_DESCRIPTION("Alan Print Test");