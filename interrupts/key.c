#include<linux/interrupt.h>
#include<linux/delay.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static int irq=1,dev=0xaa,count=0;

static irqreturn_t keyboard_handler(int irq,void *dev)
{
pr_info("keyboard counter: %d\n",count++);
return IRQ_NONE;
}
static int test_hello_init(void)
{
pr_info("%s: in init fun\n",__func__);
return request_irq(irq,keyboard_handler,IRQF_SHARED,"my_keyboard_controller",&dev);
}
static void test_hello_exit(void)
{
synchronize_irq(irq);
free_irq(irq,&dev);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
