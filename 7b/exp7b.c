//FIFO 1

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define max_buf 100

int main()
{
  char *myfifo1="myfifo1",*myfifo2="myfifo2",arr[50];
  mkfifo(myfifo1,0666);
  int i,words,lines;
  int fd;
  fgets(arr,50,stdin);
  fd=open(myfifo1,O_WRONLY);
  write(fd,arr,strlen(arr)+2);
  close(fd);
  unlink(myfifo1);
  
  int fd1;
  fd1=open(myfifo2,O_RDONLY);
  read(fd1,&i,sizeof(i));
  printf("Total characters: %d\n",i);
  read(fd1,&words,sizeof(words));
  printf("Total word: %d\n",words);
  read(fd1,&lines,sizeof(lines));
  printf("Total Lines: %d\n",lines);
  close(fd1);
}


