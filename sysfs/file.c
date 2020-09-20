#include<linux/sysfs.h>
#include<linux/kobject.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static struct kobj_attribute my_attr;

static ssize_t my_show(struct kobject *kobj,struct kobj_attribute *attr,char *buff)
{
pr_info("%s:\n",__func__);
return strlen(buff);
}
static ssize_t my_store(struct kobject *kobj,struct kobj_attribute *attr,const char *buff,size_t count)
{
pr_info("%s:\n",__func__);
return count;
}
static int test_hello_init(void)
{
pr_info("%s: in init function\n",__func__);
my_attr.attr.name="my_file";
my_attr.attr.mode=0666;
my_attr.show=my_show;
my_attr.store=my_store;
if(sysfs_create_file(kernel_kobj,&my_attr.attr))
{
pr_err("failed to create sysfs entry\n");
//return 0;
}
//else
//{
pr_info("successfully created sysfs entry\n");
//return 0;
//}
return 0;
}
static void test_hello_exit(void)
{
sysfs_remove_file(kernel_kobj,&my_attr.attr);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
