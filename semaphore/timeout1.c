#include<linux/semaphore.h>
#include<linux/slab.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
struct semaphore *mysem;
int ret;
static int test_hello_init(void)
{
pr_info("%s: in init fun\n",__func__);
sema_init(mysem,2);
pr_info("count: %d\n",&mysem->count);
ret=down_timeout(mysem,1000);
pr_info("count: %d\n",&mysem->count);
ret=down_timeout(mysem,1000);
pr_info("count: %d\n",&mysem->count);
ret=down_timeout(mysem,1000);
pr_info("count: %d and ret value: %d\n",&mysem->count,ret);
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);
