#include<linux/sysfs.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static struct kobject *my_kobj;
static int test_hello_init(void)
{
pr_info("%s: in init\n",__func__);
my_kobj=kobject_create_and_add("my_kobj",NULL);
if(!my_kobj)
{
return -ENOMEM;
}
return 0;
}
static void test_hello_exit(void)
{
kobject_del(my_kobj);
}
module_init(test_hello_init);
module_exit(test_hello_exit);

