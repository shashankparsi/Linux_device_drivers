#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
MODULE_LICENSE("GPL");
int base_minor=0;
dev_t devicenumber;
int count=0;
char *device_name="msg";
static struct class *class=NULL;
static struct device *device=NULL;
static struct cdev *mycdev;

static int device_open(struct inode *inode,struct file *file)
{
pr_info("%s: in open function\n",__func__);
return 0;
}
static int device_release(struct inode *inode, struct file *file)
{
pr_info("%s: in close function\n",__func__);
return 0;
}

static ssize_t device_read(struct file *filp, char __user *user_buffer,size_t count,loff_t *offset)
{
pr_info("%s: in read function\n",__func__);
return 0;
}
static ssize_t device_write(struct file *filp, const char __user *user_buffer,size_t count,loff_t *offset)
{
pr_info("%s: in write function\n",__func__);
char kernel_buffer[100]={0};
int retval;
pr_info("kernel buffer: %p\t , user buffer: %p\n",kernel_buffer,user_buffer);
retval=copy_from_user(kernel_buffer,user_buffer,count);
pr_info("copy from user returned: %d\n",retval);
pr_info("kernel buffer: %s\t count: %lu\t offset: %llu\n",kernel_buffer,count,*offset);
return count;
}

long device_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
pr_info("%s: in ioctl, cmd: %u\t and arg: %llu\n",__func__,cmd,arg);
return 0;
}

struct file_operations device_ops={
read:device_read,
write:device_write,
open:device_open,
release:device_release,
unlocked_ioctl:device_ioctl
};

static int __init test_hello_init(void)
{
class=class_create(THIS_MODULE,"myclass");
if(!alloc_chrdev_region(&devicenumber,base_minor,count,device_name))
{
printk("device registered successfully\n");
printk("major number recieved: %d\n",MAJOR(devicenumber));
device=device_create(class,NULL,devicenumber,NULL,device_name);
mycdev=cdev_alloc();
if(mycdev)
{
mycdev->ops=&device_ops;
mycdev->owner=THIS_MODULE;
cdev_add(mycdev,devicenumber,count);
}
}
else
{
printk("device register failed\n");
return 0;
}
}
static void __exit test_hello_exit(void)
{
device_destroy(class,devicenumber);
class_destroy(class);
cdev_del(mycdev);
unregister_chrdev_region(devicenumber,count);
}
module_init(test_hello_init);
module_exit(test_hello_exit);








