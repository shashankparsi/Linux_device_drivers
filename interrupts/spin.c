#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/gpio.h>
#include<linux/gpio.h>
#include<linux/slab.h>
#include<linux/delay.h>
#include<linux/spinlock.h>
MODULE_LICENSE("GPL");
spinlock_t *my_lock;

void is_irq_disabled(void)
{
if(irqs_disabled())
{
pr_info("interrupts are disabled\n");
}
else
{
pr_info("interrupts are enabled\n");
}
}


static int test_hello_init(void)
{
pr_info("%s: in init func\n",__func__);
my_lock=kmalloc(sizeof(spinlock_t),GFP_KERNEL);
spin_lock_init(my_lock);
is_irq_disabled();
spin_lock_bh(my_lock);
pr_info("init function locked on processor: %d\n",smp_processor_id());
is_irq_disabled();
spin_unlock_bh(my_lock);
pr_info("init function unlocked on processor: %d\n",smp_processor_id());
is_irq_disabled();
kfree(my_lock);
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit\n",__func__);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
