#include<stdio.h> 
#include<unistd.h>  
#include<string.h> 
#include<stdlib.h> 
#include <sys/types.h>
#include <unistd.h>

int main(void) 
{ 
	int fd1[2], nbytes=1,fd2[2],a=0; 
	pid_t pid; 
	char string[80]; 
	char readbuffer[80];
	char ch='a',ch1='\n';
	FILE *fp; 
	
	pipe(fd1);//PIPE CREATED
	pipe(fd2);//PIPE CREATED 

	/*Error in fork*/
	if((pid = fork()) == -1) 
	{ 
		perror("fork"); 
		exit(1); 
	} 

	//Child Process
	if(pid == 0) 
	{  
		close(fd1[1]);           /*closing write end of Pipe 1*/
		read(fd1[0], readbuffer, sizeof(readbuffer));     /*reading filename through Pipe 1*/
		printf("\nFilename '%s' is being read by Child Process through Pipe 1...\n",readbuffer);
		fp=fopen(readbuffer,"r");
		close(fd1[0]);         /*closing read end of Pipe 1*/
		close(fd2[0]);        /*closing read end of Pipe 2*/
		printf("\nContents of %s are being sent to Parent Process through Pipe 2...\n",readbuffer);
		while(a!=-1)
		{
			a=fscanf(fp,"%c",&ch);
			write(fd2[1], &ch, sizeof(ch));   /*writing contents of file on Pipe 2*/
		} 
		close(fd2[1]); /*closing write end of Pipe 2*/
		exit(0); 
	} 
	//Parent process
	else 
	{  
		close(fd1[0]); /*closing read end of Pipe 1*/
		printf("IN PARENT PROCESS\n" );
		printf("\nEnter name of file:");
		scanf("%s",string); 
		printf("Filename is being sent by Parent Process to Child Process through Pipe 1...\n"); 
		write(fd1[1], string, (strlen(string)+1));  /*writing filename on Pipe 1*/
		wait();
		close(fd1[1]); /*closing write end of Pipe 1*/
		close(fd2[1]);  /*closing write end of Pipe 2*/

		printf("\nContents of %s are being received by Parent Process through Pipe 2...\n\n",string);
		printf("IN PARENT PROCESS\n" );
		printf("\nReceived Message:\n");

		while(nbytes!=0) 
		{
			printf("%c",ch1);
			nbytes = read(fd2[0], &ch1, sizeof(ch1));   /*reading contents of file from Pipe 2*/
		} 
		close(fd2[0]); /*closing read end of Pipe 2*/
	} 
	return(0); 
} 

