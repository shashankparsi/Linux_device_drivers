#include<linux/ioport.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
#define MY_BASEPORT 0x0062
#define NUMBER_PORTS 2
static int test_hello_init(void)
{
if(!request_region(MY_BASEPORT,NUMBER_PORTS,"myports"))
{
pr_info("request ioports are failed to assign\n");
return -1;
}
else
{
pr_info("ports assigned successfully\n");
outb(0xa,MY_BASEPORT);
}
return 0;
}
static void test_hello_exit(void)
{
int a;
a=inb(MY_BASEPORT);
pr_info("value at %02x is  %02x\n",MY_BASEPORT,a);
release_region(MY_BASEPORT,NUMBER_PORTS);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
