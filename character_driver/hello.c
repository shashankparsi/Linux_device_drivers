#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/fcntl.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include"ioctl_cmd.h"
MODULE_LICENSE("GPL");
static struct class *myclass=NULL;
static struct device *mydevice=NULL;
static struct cdev mycdev;
int base_minor=0;
char *device_name="myowndevice";
int count=1;
dev_t devicenumber;


static int device_open(struct inode *inode,struct file *file)
{
pr_info("%s: in open function\n",__func__);
return 0;
}
static int device_release(struct inode *inode,struct file *file)
{
pr_info("%s: in release function\n",__func__);
return 0;
}

static ssize_t device_read(struct file *filp,char __user *user_buffer,size_t count,loff_t *offset)
{
char kernel_buffer[100]="welcome kernel";
int retval;
retval=copy_to_user(user_buffer,kernel_buffer,20);
pr_info("%s: string length: %lu\n",__func__,strlen(kernel_buffer));
pr_info("%s:copy to user returned: %d\n",__func__,retval);
pr_info("%s: kernel_buffer: %s\t, count: %lu\t and offset: %llu\n",__func__,kernel_buffer,count,*offset);
return 0;
}
static ssize_t device_write(struct file *filp,const char __user *user_buffer,size_t count,loff_t *offset)
{
char kernel_buffer[100]={0};
int retval;
pr_info("%s: kernel_buffer: %p and user_buffer: %p\n",kernel_buffer,user_buffer);
pr_info("%sL strlen of user_buffer: %lu\n",__func__,strnlen_user(user_buffer,100));
retval=copy_from_user(kernel_buffer,user_buffer,20);
pr_info("%s: copy from user returned: %lu\n",__func__,retval);
pr_info("%s: kernel_buffer: %s\t , count : %lu\t ,offset: %llu\n",__func__,kernel_buffer,count,*offset);
return count;
}


long device_ioctl(struct file *filp,unsigned int cmd, unsigned long arg)
{
unsigned char ch;
pr_info("%s: in ioctl function\n",__func__);
pr_info("%s: cmd:%u\t and arg: %lu\n",__func__,cmd,arg);
/*switch(cmd)
{
case MSG_IOCTL_GET_LENGTH:
	pr_info("get buffer length\n");
	put_user(1024,(unsigned int *)arg);
	break;
case MSG_IOCTL_CLR_BUFFER:
	pr_info("clear buffer\n");
	memset(kernel_buffer,0,sizeof(kernel_buffer));
	break;
case MSG_IOCTL_FILL_BUFFER:
	pr_info("filling buffer\n");
	getuser(ch,(unsigned int*)arg);
	pr_info("fill character: %c\n",ch);
	memset(kernel_buffer,ch,sizeof(kernel_buffer));
	break;
default :
	pr_info("unknwn command\n");
	exit(0);
}*/
return 0;
}


static struct file_operations device_fops={
.read=device_read,
.write=device_write,
.open=device_open,
.release=device_release,
.unlocked_ioctl=device_ioctl
};

static int __init test_hello_init(void)
{
myclass=class_create(THIS_MODULE,"myclass");
if(!(alloc_chrdev_region(&devicenumber,base_minor,count,device_name)))
{
pr_info("device number registered\n");
pr_info("major number received: %d\n",MAJOR(devicenumber));
mydevice=device_create(myclass,NULL,devicenumber,NULL,"mydevice");
cdev_init(&mycdev,&device_fops);
mycdev.owner=THIS_MODULE;
cdev_add(&mycdev, devicenumber,count);
}
else
{
pr_info("device failed\n");
}
return 0;
}
static void __exit test_hello_exit(void)
{
//class_destroy(myclass);
device_destroy(myclass,devicenumber);
class_destroy(myclass);
cdev_del(&mycdev);
unregister_chrdev_region(devicenumber,count);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
