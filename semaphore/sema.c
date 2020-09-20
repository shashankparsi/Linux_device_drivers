#include<linux/semaphore.h>
#include<linux/slab.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static struct semaphore *mysem;
static int test_hello_init(void)
{
pr_info("%s: in init func\n",__func__);
mysem=kmalloc(sizeof(mysem),GFP_KERNEL);
sema_init(mysem,1);
down(mysem); //dec mysem value by 1
pr_info("%s:entering in to critical region\n",__func__);
pr_info("%s: exiting the critical region\n",__func__);
up(mysem);//inc mysem value by 1
kfree(mysem);
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);

