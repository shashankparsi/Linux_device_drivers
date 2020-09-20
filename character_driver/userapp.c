#include<stdio.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include"ioctl_cmd.h"
int main()
{
unsigned int length;
char buffer[1024];
unsigned char ch='A';

int fd;
fd=open("/dev/mydevice",O_RDWR);
perror("open");
ioctl(fd,MSG_IOCTL_GET_LENGTH,&length);
printf("length : %d\n",length);
perror("ioctl");
ioctl(fd,MSG_IOCTL_FILL_BUFFER,&ch);
//lseek(fd,0,SEEK_SET);
length=read(fd,buffer,1024);
printf("length: %d\n",length);
buffer[1023]='\0';
printf("buffer: %s\n",buffer);
getchar();
lseek(fd,0,SEEK_SET);
length=write(fd,"hello kernel",sizeof(buffer));
printf("length: %d\n",length);
length=read(fd,buffer,1024);
printf("length: %d\n",length);

ioctl(fd,0x02);
perror("ioctl");
getchar();
close(fd);
return 0;
}
