#include<linux/interrupt.h>
#include<linux/delay.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static int irq=19,dev,count=0;

static irqreturn_t my_interrupt(int irq,void *dev)
{
count++;
pr_info("in the ISR: count=%d\n",count);
return IRQ_HANDLED;
}

static int test_hello_init(void)
{
pr_info("%s: in init\n",__func__);
if(request_irq(irq,my_interrupt,IRQF_SHARED,"ethinterrupt",&dev))
{
pr_info("failed to register interrupt\n");
}
pr_info("successfully loading ISR handled\n");
return 0;
}
static void test_hello_exit(void)
{
synchronize_irq(irq);
free_irq(irq,&dev);
}
module_init(test_hello_init);
module_exit(test_hello_exit);
