#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<generated/utsrelease.h>
MODULE_LICENSE("GPL");
static int __init test_hello_init(void)
{
pr_info("%s: in init\n",__func__);
pr_info("LINUX_VERSION_CODE: %u\n",LINUX_VERSION_CODE);
pr_info("kernel version: %u\n",KERNEL_VERSION(5,3,0));
pr_info("UTS release: %s\n",UTS_RELEASE);
return 0;
}
static void __exit test_hello_exit(void)
{
pr_info("%s: in exit\n",__func__);
}
module_init(test_hello_init);
module_exit(test_hello_exit);

