#include<sys/io.h>
#include<stdio.h>
#include<errno.h>
int main()
{
if(ioperm(0x70,3,1))
{
perror("ioperm failed\n");
return -1;
}
else
{
printf("ioperm success\n");
}
return 0;
}
