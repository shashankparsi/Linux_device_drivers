#include<linux/slab.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<asm/io.h>
MODULE_LICENSE("GPL");
static void *ptr;
int alloc_size=1024;
int i=0;
static int test_hello_init(void)
{
phys_addr_t physical_address;
for( i=0;i<=8192;i++)
{
ptr=kmalloc(alloc_size,GFP_DMA);
if(!ptr)
{
pr_info("memory allocation failed\n");
return -ENOMEM;
}
pr_info("virtual address of ptr: %px\n",ptr);
physical_address=virt_to_phys(ptr);
pr_info("physical address of ptr: %px\n",&physical_address);
pr_info("size is %lu\n",ksize(ptr));
kfree(ptr);
ptr=kmalloc(alloc_size,GFP_DMA32);
pr_info("virtual address of ptr: %px\n",ptr);
physical_address=virt_to_phys(ptr);
pr_info("physical address of ptr: %px\n",&physical_address);
kfree(ptr);
}
return 0;
}
static void test_hello_exit(void)
{
//kfree(ptr);
//kfree(ptr);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
