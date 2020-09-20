#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>
int main()
{
fd_set readset,writeset,exceptset;
FD_ZERO(&readset);
FD_ZERO(&writeset);
FD_ZERO(&exceptset);
printf("fd set of stdin: %d\n",fileno(stdin));
FD_SET(fileno(stdin),&readset);
printf("calling select....\n");
int retval=select(fileno(stdin)+1,&readset,&writeset,&exceptset,NULL);
printf("select returned: %d\n",retval);
return 0;
}
