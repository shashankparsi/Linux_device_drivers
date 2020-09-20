#include<linux/ioport.h>
#include<linux/kernel.h>
#include<linux/module.h>
#define INTEL_RNG_HW_STATUS 0
#define INTEL_RNG_PRESENT 0x40
#define INTEL_RNG_ENABLED 0x01
#define INTEL_RANDOM_GENERATOR_ADDR 0XFFBC015F
#define LENGTH 3
MODULE_LICENSE("GPL");

static inline unsigned char hw_status_get(void __iomem *p)
{
return ioread8(p+INTEL_RNG_HW_STATUS);
}
static int test_hello_init(void)
{
if(!(request_mem_region(INTEL_RANDOM_GENERATOR_ADDR,LENGTH,"myrng")))
{
pr_info("requested mem region failed\n");
return -1;
}
else
{
unsigned char hw_status;
void __iomem *p;
pr_info("requested region success\n");
p=ioremap(INTEL_RANDOM_GENERATOR_ADDR,LENGTH);
pr_info("ioremap returns: %02x\n",p);
hw_status=hw_status_get(p);
pr_info("hw_status returned: %02x\n",hw_status);

if((hw_status & INTEL_RNG_PRESENT)==0)
{
pr_warn("random number genrator is not present\n");
}
else
{
pr_info("random number generator is present\n");
}
if((hw_status & INTEL_RNG_ENABLED)==0)
{
pr_warn("RNG is disabled\n");
}
else
{
pr_info("RNG is enabled\n");
}
iounmap(p);
}
return 0;
}
static void test_hello_exit(void)
{
release_mem_region(INTEL_RANDOM_GENERATOR_ADDR,LENGTH);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
