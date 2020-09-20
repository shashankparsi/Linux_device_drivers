#include<sys/mman.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
int fd;
char ch='a';
void *mem;
fd=open("/dev/mem",O_RDWR|O_SYNC);
if(fd<0)
{
perror("open failed\n");
return -1;
}
mem=mmap(NULL,0xfff,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x101f1000);
if(mem==(void *)-1)
{
perror("mmap failed\n");
close(fd);
return -2;
}
*(unsigned char *)mem=ch;
munmap(mem,0xfff);
return 0;
}
