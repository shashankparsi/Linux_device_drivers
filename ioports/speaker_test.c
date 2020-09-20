#include<sys/io.h>
#include<stdio.h>
#include<errno.h>
#define SPEAKER_PORT 0x61
int main()
{
ioperm(SPEAKER_PORT,1,1);
outb(0x03,SPEAKER_PORT);
sleep(5);
outb(0x00,SPEAKER_PORT);
return 0;
}
