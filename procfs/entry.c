#include<linux/proc_fs.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static struct proc_dir_entry *embedded_pde;
static int test_hello_init(void)
{
pr_info("%s: in init\n",__func__);
embedded_pde=proc_mkdir("embedded",NULL);
if(!(embedded_pde))
{
pr_info("error in creating prod directory\n");
return -1;
}
pr_info("proc directory created successfully\n");
return 0;
}
static void test_hello_exit(void)
{
remove_proc_entry("embedded",NULL);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
