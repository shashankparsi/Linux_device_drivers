#include<linux/ioctl.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#define MAGIC_NUMBER1 'l'
#define MAGIC_NUMBER2 'i'
int main()
{
printf("IO(MAGIC_NUMBER1,1): %x\n",_IO(MAGIC_NUMBER1,1));
printf("IO(MAGIC_NUMBER2,1): %x\n",_IO(MAGIC_NUMBER2,1));
getchar();
printf("_IO(MAGIC_NUMBER1,1): %x\n",_IO(MAGIC_NUMBER1,2));
printf("_IO(MAGIC_NUMBER2,1): %X\n",_IO(MAGIC_NUMBER2,2));
getchar();
printf("_IOR(MAGIC_NUMBER1,1): %x\n",_IOR(MAGIC_NUMBER1,3,int));
printf("_IOR(MAGIC_NUMBER2,1): %X\n",_IOR(MAGIC_NUMBER2,3,int));
getchar();
printf("_IOR(MAGIC_NUMBER1,1): %x\n",_IOR(MAGIC_NUMBER1,4,int));
printf("_IO(MAGIC_NUMBER2,1): %x\n",_IOR(MAGIC_NUMBER2,4,int));
getchar();
printf("_IOWR(MAGIC_NUMBER1,1): %x\n",_IOWR(MAGIC_NUMBER1,6,int));
printf("_IOWR(MAGIC_NUMBER2,1): %x\n",_IOWR(MAGIC_NUMBER2,6,int));  
return 0;
}


