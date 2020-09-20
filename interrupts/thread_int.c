#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/interrupt.h>
#include<linux/delay.h>
MODULE_LICENSE("GPL");
static int irq=19,my_dev_id,irq_counter=0;


static irqreturn_t  interrupt_handler(int irq,void *dev_id)
{
pr_info("in interrupt handler\n");
return IRQ_NONE;
}

static irqreturn_t thread_function(int irq,void *dev_id)
{
pr_info("in interrupt threaded function\n");
//return IRQ_WAKE_THREAD;
return IRQ_HANDLED;
}

static int test_hello_init(void)
{
int ret;
ret=request_threaded_irq(irq,interrupt_handler,thread_function,IRQF_SHARED,"my_interrupt",&my_dev_id);
if(ret==0)
{
pr_info("interrupr registered successfully\n");
return 0;
}
else
{
pr_info("interrupt registration failed\n");
return -1;
}
return 0;
}

static void test_hello_exit(void)
{
synchronize_irq(irq);
free_irq(irq,&my_dev_id);
pr_info("counter: %d\n",irq_counter++);
pr_info("interrupt freed\n");
}
module_init(test_hello_init);
module_exit(test_hello_exit);
