#include<linux/kthread.h>
#include<asm/io.h>
#include<linux/kernel.h>
#include<linux/delay.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static struct task_struct *my_thread;

int thread_fn(void *pv)
{
int i=0;
while(!(kthread_should_stop()))
{
pr_info("%s: thread function running on : %d\n",__func__,smp_processor_id());
msleep(1000);
}
return 0;
}

static int test_hello_init(void)
{
pr_info("%s: init process running in : %d\n",__func__,smp_processor_id());
my_thread=kthread_create(thread_fn,NULL,"mythread");
if(my_thread)
{
wake_up_process(my_thread);
return 0;
}
else
{
pr_info("thread creation failed\n");
return -1;
}
return 0;
}

static void test_hello_exit(void)
{
pr_info("%s: in exit function ... running in : %d\n",__func__,smp_processor_id());
kthread_stop(my_thread);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
