#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/ioport.h>
MODULE_LICENSE("GPL");
#define PCI_INDEX_PORT 0xcf8h
#define PCI_DATA_PORT 0xcfch

unsigned short read_pci_config_short(unsigned char bus,unsigned char slot,unsigned char func,unsigned char offset)
{
outl(0x80000000 | (bus<<16) |(slot<<11) | (func<<8)|offset,0xcf8);
return inw(0xcfc+(offset&2));
}

static int test_hello_init(void)
{
unsigned short vendor_id;
unsigned short device_id;
vendor_id=read_pci_config_short(0,0,0,0);
device_id=read_pci_config_short(0,0,0,2);
pr_info("vendor_id: %02x\t device_id:%02x\n",vendor_id,device_id);
vendor_id=read_pci_config_short(0,1,0,0);
device_id=read_pci_config_short(0,1,0,2);
pr_info("vendor_id: %02x\t device_id:%02x\n",vendor_id,device_id);
return 0;
}
static void test_hello_exit(void)
{
}
module_init(test_hello_init);
module_exit(test_hello_exit);
