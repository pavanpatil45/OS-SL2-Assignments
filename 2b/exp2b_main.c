#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void sort(int a[10]);

int main(int argc,char *argv[])
{
int pid;
int i=0,n=10,search;
char *env[]={NULL};
int a[11];

char *newarg[]={NULL,"sort.txt", NULL};
newarg[0]=argv[1];

printf("Enter array elements : ");
for(i=1;i<=10;i++)
scanf(" %d",&a[i]);



printf("Enter value to find : ");
scanf("%d", &search);
FILE *f;
pid=fork();

if(pid==0)
{
sleep(1);
execve(argv[1],newarg,env);
}
else
{

sort(a);
f=fopen("sort.txt","w");

fprintf(f," %d",search);
for(i=1;i<=n;i++)
{
fprintf(f," %d",a[i]);
}

}
fclose(f);

}

void sort(int a[10])
{
int n=10, i=0, j=0, temp;
for(i=1; i<=n; i++)
{
for(j=1; j<n; j++)
{
if(a[i]<a[j])
{
temp=a[i];
a[i]=a[j];
a[j]=temp;
}
}
}
}
