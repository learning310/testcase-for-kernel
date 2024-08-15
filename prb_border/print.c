#include <linux/delay.h>
#include <linux/cpumask.h>
#include <linux/smp.h>
#include <linux/kthread.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int print_thread(void *data)
{
	struct task_struct *tsk = current;
	char name[sizeof(tsk->comm)];
	for (;;) {
		get_task_comm(name, tsk);
		// printk("alan: cpuid=%d, name=%s\n", smp_processor_id(), name); // for data ring rollback
		printk("a"); // for desc ring rollback

		msleep(10);
	}
	return 0;
}

static struct task_struct *task = NULL;
static int __init test_init(void)
{
	int i;
	for (i = 0; i < num_online_cpus(); i++) {
		task = kthread_create_on_node(print_thread, NULL,
					      cpu_to_node(i), "print_thread_%d",
					      i);
		if (IS_ERR(task)) {
			printk("alan: Unable to start kernel thread.");
		}
		kthread_bind(task, i);
		wake_up_process(task);
	}

	return 0;
}

static void __exit print_exit(void)
{
	printk("alan: exit");
}

module_init(test_init);
module_exit(print_exit);
MODULE_INFO(intree, "Y");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan Song");
MODULE_DESCRIPTION("Alan Print Test");
