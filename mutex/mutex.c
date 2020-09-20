#include<linux/mutex.h>
#include<linux/semaphore.h>
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/module.h>
int ret;
MODULE_LICENSE("GPL");
static struct mutex *my_lock;
static int test_hello_init(void)
{
pr_info("%s: in init fun\n",__func__);
my_lock=kmalloc(sizeof(my_lock),GFP_KERNEL);
mutex_init(my_lock);
//pr_info("value of ret is : %d\n",ret);
mutex_lock(my_lock);
mutex_is_locked(my_lock);
pr_info("entering in to critical sectio\n");
pr_info("exiting critical section\n");
mutex_unlock(my_lock);
kfree(my_lock);
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);

