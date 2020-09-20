#include<linux/list.h>
#include<linux/module.h>
#include<linux/kernel.h>
MODULE_LICENSE("GPL");
LIST_HEAD(listhead);
static int test_hello_init(void)
{
pr_info("%s: in init\n",__func__);
pr_info("%s: listhead: %px\t , listhead.next:%px\t , listhead.prev:%px\n",__func__,listhead,listhead.next,listhead.prev);
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit\n",__func__);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
