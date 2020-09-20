#include<linux/ioport.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
#define MY_BASEADDRESS 0xf800000
#define LENGTH 0xf
static int test_hello_init(void)
{
pr_info("%s: in init\n",__func__);
if(!(request_mem_region(MY_BASEADDRESS,LENGTH,"mymemports")))
{
pr_info("requested mem region failed\n");
}
else
{
void __iomem *p;
pr_info("requested mem region success\n");
p=ioremap(MY_BASEADDRESS,LENGTH);
pr_info("ioremap returned: %px\n",p);
iounmap(p);
}
return 0;
}
static void test_hello_exit(void)
{
pr_info("%s: in exit\n",__func__);
release_mem_region(MY_BASEADDRESS,LENGTH);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
