#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>
int main()
{
fd_set fds;
FD_ZERO(&fds);
FD_SET(0,&fds);
if(FD_ISSET(0,&fds))
{
printf("FD 0 is set\n");
}
else
{
printf("FD 0 is not set\n");
}
FD_CLR(0,&fds);
if(FD_ISSET(0,&fds))
{
printf("FD 0 is set\n");
}
else
{
printf("FD 0 is not set\n");
}
return 0;
}
