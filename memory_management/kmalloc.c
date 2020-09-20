#include<linux/slab.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
MODULE_LICENSE("GPL");
static void *ptr;
int alloc_size=1024;
module_param(alloc_size,int,0);
static int test_hello_init(void)
{
ptr=kmalloc(alloc_size,GFP_ATOMIC);
if(!ptr)
{
pr_info("memory allocation failed\n");
return -1;
}
else
{
phys_addr_t physical_address=virt_to_phys(ptr);
pr_info("physical address of ptr is : %px\n",&physical_address);
pr_info("memory allocated: %px\n",ptr);
return 0;
}
}
static void test_hello_exit(void)
{
kfree(ptr);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
