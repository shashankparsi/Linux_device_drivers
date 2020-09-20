#include<linux/kthread.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched/signal.h>
#include<linux/delay.h>
static struct task_struct *my_thread;

int thread_fn(void *pv)
{
int i=0;
while(!kthread_should_stop())
{
printk(KERN_INFO "in thread function %d\n",i++);
msleep(1000);
}
return 0;
}

static int test_hello_init(void)
{
my_thread=kthread_create(thread_fn,NULL,"mythread");
if(my_thread)
{
wake_up_process(my_thread);
return 0;
}
else
{
printk(KERN_INFO "thread cannot be created\n");
return -1;
}
}
static  void test_hello_exit(void)
{
kthread_stop(my_thread);
printk(KERN_INFO "in exit function\n");
}
module_init(test_hello_init);
module_exit(test_hello_exit);
MODULE_LICENSE("GPL");
