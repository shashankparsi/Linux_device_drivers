#include<linux/ioport.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/delay.h>
MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
outb(0x03,0x0061);
ssleep(5);
outb(0x00,0x0061);
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);
