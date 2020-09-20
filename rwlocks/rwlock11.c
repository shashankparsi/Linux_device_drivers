//#include<linux/rwlock_types.h>
//#include<linux/semaphore.h>
//#include<linux/mutex.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<linux/kthread.h>
//#include<linux/spinlock.h>
#include<linux/delay.h>
MODULE_LICENSE("GPL");
DEFINE_RWLOCK(mylock);
//struct rwlock_t *mylock;
static struct task_struct *thread1,*thread2,*thread3;
static int counter=0;
static int write_fun(void *arg)
{
while(!(kthread_should_stop()))
{
pr_info("processor : %d is acquring the write lock\n",smp_processor_id());
write_lock(&mylock);
pr_info("processor: %d acquired writed lock\n",smp_processor_id());
counter++;
mdelay(3000);
write_unlock(&mylock);
pr_info("processor : %d released write lock\n",smp_processor_id());
}
return 0;
}

static int read_fun(void *arg)
{
while(!(kthread_should_stop()))
{
pr_info("processor: %d acquring thr read lock\n",smp_processor_id());
read_lock(&mylock);
pr_info("processor: %d acquired the read lock\n",smp_processor_id());
counter++;
mdelay(3000);
read_unlock(&mylock);
pr_info("processor: %d released the write lock\n",smp_processor_id());
}
return 0;
}
static int test_hello_init(void)
{
//rwlock_init(mylock);
thread1=kthread_run(read_fun,NULL,"readthread");
thread2=kthread_run(read_fun,NULL,"readthread");
thread3=kthread_run(write_fun,NULL,"writethread");
return 0;
}
static void test_hello_exit(void)
{
kthread_stop(thread1);
kthread_stop(thread2);
kthread_stop(thread3);
}

module_init(test_hello_init);
module_exit(test_hello_exit);


