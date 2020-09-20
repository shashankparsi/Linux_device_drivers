#include<linux/spinlock.h>
#include<linux/slab.h>
#include<linux/kernel.h>
#include<linux/kthread.h>
#include<linux/module.h>
#include<linux/delay.h>
#include<linux/sched.h>
#include<linux/init.h>
MODULE_LICENSE("GPL");
DEFINE_SPINLOCK(my_counter);
static struct task_struct *read_thread,*write_thread;
unsigned int counter=0;
static int read_fun(void *data)
{
while(!(kthread_should_stop()))
{
spin_lock(&my_counter);
pr_info("counter: %d\n",counter);
spin_unlock(&my_counter);
msleep(500);
pr_info("read fun running in processor: %d\n",smp_processor_id());
}
do_exit(0);
//pr_info("read fun running in processor: %d\n",smp_processor_id());
}
static int write_fun(void *data)
{
while(!(kthread_should_stop()))
{
spin_lock(&my_counter);
counter++;
spin_unlock(&my_counter);
msleep(500);
pr_info("write fun running in processor: %d\n",smp_processor_id());
}
do_exit(0);
//pr_info("write fun running in processor: %d\n",smp_processor_id());
}

static int test_hello_init(void)
{
pr_info("entering module...\n");
counter=0;
read_thread=kthread_run(read_fun,NULL,"read-thread");
write_thread=kthread_run(write_fun,NULL,"write-thread");
return 0;
}
static void test_hello_exit(void)
{
kthread_stop(read_thread);
kthread_stop(write_thread);
pr_info("exiting module\n");
}
module_init(test_hello_init);
module_exit(test_hello_exit);
