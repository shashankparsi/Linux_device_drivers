#include<linux/sched.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
pr_info("%s: in init process: %d\n",__func__,smp_processor_id());
set_current_state(TASK_INTERRUPTIBLE);
schedule();
pr_info("%s: after schedule: %d\n",__func__,smp_processor_id());
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit: %d\n",__func__,smp_processor_id());
}
module_init(test_hello_init);
module_exit(test_hello_exit);
