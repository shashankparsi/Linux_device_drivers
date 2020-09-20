#include<asm/atomic.h>
//#include<asm/bitops.h>
//#include<linux/bitops.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
unsigned long addr=0x50;
static int test_hello_init(void)
{
pr_info("%s: value before settin: %02lx\n",__func__,addr);
set_bit(0,&addr);
pr_info("%s: value after setting the 0th bit: %02lx\n",__func__,addr);
clear_bit(4,&addr);
pr_info("%s: value afer clearing bit 4: %02lx\n",__func__,addr);
change_bit(0,&addr);
pr_info("%s: value after changing bit 0 : %02lx\n",__func__,addr);
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);
