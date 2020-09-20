#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/spinlock.h>
#include<linux/slab.h>
#include<linux/delay.h>
MODULE_LICENSE("GPL");
//DEFINE_SPINLOCK(my_lock);
spinlock_t *my_lock;
static int test_hello_init(void)
{
pr_info("%s: in init\n",__func__);
my_lock=kmalloc(sizeof(spinlock_t),GFP_KERNEL);
spin_lock_init(my_lock);
spin_lock(my_lock);
pr_info("entering in to critical region\n");
msleep(5000);
pr_info("...............................\n");
pr_info("%s: exiting the critical region\n");
spin_unlock(my_lock);
kfree(my_lock);
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);
