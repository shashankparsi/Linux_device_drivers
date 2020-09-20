#include<asm/atomic.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
atomic_t val=ATOMIC_INIT(0); // val=0
static int test_hello_init(void)
{
pr_info("%s: value after initialization: %d\n",__func__,atomic_read(&val));
atomic_set(&val,10);
pr_info("%s: after setting value to 10: %d\n",__func__,atomic_read(&val));
atomic_dec(&val);
pr_info("%s: after dec by 1 value is : %d\n",__func__,atomic_read(&val));
atomic_inc(&val);
pr_info("%s: after inc by 1 value is : %d\n",__func__,atomic_read(&val));
atomic_add(20,&val);
pr_info("%s: after adding 20 value is: %d\n",__func__,atomic_read(&val));
atomic_sub(5,&val);
pr_info("%s: after sub 5 value is %d\n",__func__,atomic_read(&val));
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit %d\n",__func__,__LINE__);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
