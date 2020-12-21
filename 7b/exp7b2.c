//FIFO 2

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define max_buf 100

int main()
{
  char *myfifo1="myfifo1",*myfifo2="myfifo2";
  char buf[50];
  FILE *fp;
  int i=0,words=0,lines=0;
  mkfifo(myfifo2,0777);
  int fd,fd1;
  fd=open(myfifo1,O_RDWR);
  read(fd,buf,max_buf);
  printf("\nMessage received is: %s",buf);
  while(buf[i]!='\0')
  {
    while(buf[i]==' ')
    {
      words++,i++;
    }
    if(buf[i]=='.'||buf[i]=='?'||buf[i]=='!')
    {
      lines++,i++;
    }
    i++;
  }
  
  printf("\n Total no. of characters:%d",i);
   fp=fopen("abc.txt","w+");
   fprintf(fp,"Total characters=%d",i);
   
   printf("\n Total no. of words:%d",words);
   fp=fopen("abc.txt","w+");
   fprintf(fp,"Total characters=%d",words);
   
   printf("\n Total no. of characters:%d",lines);
   fp=fopen("abc.txt","w+");
   fprintf(fp,"Total no. of lines=%d",lines);
   fclose(fp);
   unlink(myfifo1);
   
   fd1=open(myfifo2,O_RDWR);
   write(fd1,&i,sizeof(i));
   write(fd1,&words,sizeof(words));
   write(fd1,&lines,sizeof(lines));
   close(fd1);
  return 0;
}