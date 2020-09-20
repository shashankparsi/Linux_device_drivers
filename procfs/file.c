#include<linux/proc_fs.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
MODULE_LICENSE("GPL");
static struct proc_dir_entry *dir_entry;

static ssize_t myread(struct file *file, char __user *ubuff,size_t count,loff_t *ppos)
{
pr_info("in read handler\n");
return count;
}
static ssize_t mywrite(struct file *file, const char __user *ubuff,size_t count, loff_t *ppos)
{
pr_info("in write handler\n");
return count;
}

static struct file_operations proc_fs={
owner:THIS_MODULE,
read:myread,
write:mywrite
};

static int test_hello_init(void)
{
pr_info("%s: in init\n",__func__);

dir_entry=proc_mkdir("shashank",NULL);
proc_create("embedded",0777,dir_entry,&proc_fs);
if(!(dir_entry))
{
pr_info("failed\n");
return -1;
}
pr_info("file success\n");
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit\n",__func__);
remove_proc_entry("shashank",NULL);
remove_proc_entry("embedded",NULL);
}
module_init(test_hello_init);
module_exit(test_hello_exit);


