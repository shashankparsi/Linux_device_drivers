#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/kernel.h>
#include<linux/module.h>
int major_number;
int minor_number;
char *device_name="mychardev";
dev_t devicenumber;
int count=1;
MODULE_LICENSE("GPL");
MODULE_AUTHOR("shashank parsi");
module_param(major_number,int,0);
module_param(minor_number,int, 0);
module_param(device_name,charp,0);
module_param(count,int,0);
static int test_hello_init(void)
{
devicenumber=MKDEV(major_number,minor_number);
printk(KERN_INFO "major number is : %d\n",MAJOR(devicenumber));
printk(KERN_INFO "minor number is : %d\n",MINOR(devicenumber));
printk(KERN_INFO "count is %d\n",count);
printk(KERN_INFO "device name is %s\n",device_name);
if(!(alloc_chrdev_region(&devicenumber,minor_number,count,device_name)))
{
printk("device number registerd!!!\n");
}
else
{
printk("device number not registered!!\n");
return 0;
}
}
static void test_hello_exit(void)
{
unregister_chrdev_region(devicenumber,count);
}
module_init(test_hello_init);
module_exit(test_hello_exit);


