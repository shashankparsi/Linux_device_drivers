#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched/signal.h>
#include<linux/cpumask.h>
char buffer[256];
char *get_task_state(long state)
{
switch(state)
{
case TASK_RUNNING:
	return "task running";
case TASK_INTERRUPTIBLE:
	return "task interruptible";
case TASK_UNINTERRUPTIBLE:
	return "task uninterruptible";
case TASK_STOPPED:
	return "task stopped";
case TASK_TRACED:
	return "task traced";
default:
{
sprintf(buffer,"unknown type: %ld\n",state);
return buffer;
}
}
}
static int test_task_init(void)
{
struct task_struct *task_list;
unsigned int process_count=0;
pr_info("%s: in init func and line number: %d\n",__func__,__LINE__);
for_each_process(task_list)
{
pr_info("process : %s\t PID: [%d]\t  state: %s\n",task_list->comm,task_list->pid,get_task_state(task_list->state));
process_count++;
}
pr_info("number of process: %d\n",process_count);
pr_info("number of processors: %d\n",num_online_cpus());
return 0;
}
static void test_task_exit(void)
{
pr_info("%s: in exit\n",__func__);
}
module_init(test_task_init);
module_exit(test_task_exit);

MODULE_LICENSE("GPL");

