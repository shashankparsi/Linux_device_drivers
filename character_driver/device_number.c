#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
char buffer[20];
dev_t devicenumber;
devicenumber=MKDEV(120,30);
printk("device number: %s\n" ,format_dev_t(buffer,devicenumber));
buffer[0]='\0';
printk("print_dev_t returned: %d\t device number: %s\n",print_dev_t(buffer,devicenumber),buffer);
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit\n",__func__);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
