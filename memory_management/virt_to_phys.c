#include<asm/io.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
int i=0;
void *virtual_address=(void *)&i;
phys_addr_t physical_address=virt_to_phys(virtual_address);
pr_info("virtual address of i: %px\n",virtual_address);
pr_info("physical address of i: %px\n",physical_address);
pr_info("virtual address of i :%px\n",phys_to_virt(physical_address));
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);
