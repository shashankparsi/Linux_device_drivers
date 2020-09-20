#include<linux/interrupt.h>
#include<linux/delay.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");

void tasklet_function(unsigned long data)
{
pr_info("%s: in tasklet handler, data: %s\n",__func__,(char *)data);
}

char tasklet_data[]="linux is easy";
DECLARE_TASKLET(my_tasklet,tasklet_function,(unsigned long)&tasklet_data);
DECLARE_TASKLET_DISABLED(my_tasklet_disabled,tasklet_function,(unsigned long)&tasklet_data);
static int test_hello_init(void)
{
pr_info("%s: in init func\n",__func__);
pr_info("state: %ld\n",my_tasklet.state);
pr_info("count: %d\n",atomic_read(&my_tasklet.count));
tasklet_hi_schedule(&my_tasklet);
pr_info("state:%ld\n",my_tasklet_disabled.state);
pr_info("count: %d\n",atomic_read(&my_tasklet_disabled.count));
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit\n",__func__);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
