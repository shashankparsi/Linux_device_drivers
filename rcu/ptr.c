#include<linux/rcupdate.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<linux/kthread.h>
MODULE_LICENSE("GPL");
static struct task_struct *thread;
typedef struct my_data
{
int key;
int value;
}my_data;
my_data *global_ptr=NULL;

static int thread_fun(void *data)
{
my_data *new_ptr=kmalloc(sizeof(my_data),GFP_KERNEL);
new_ptr->key=1;
new_ptr->value=1000;
rcu_assign_pointer(global_ptr,new_ptr);
pr_info("global_pointer key: %d\t value: %d\n",global_ptr->key,global_ptr->value);
return 0;
}
static int test_hello_init(void)
{
thread=kthread_run(thread_fun,NULL,"thread");
return 0;
}
static void test_hello_exit(void)
{
kthread_stop(thread);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
