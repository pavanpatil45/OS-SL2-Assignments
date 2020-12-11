#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
 
void bsearch(int a[10], int search);

int main(int argc,char *argv[])
{
int a[11],i,n=10,search,first, last, middle,flag=0;
FILE *f;

f=fopen(argv[1],"r");

printf(" %s",argv[1]);
fscanf(f,"%d",&search);

printf(" Key=%d\n",search);

for(i=0;i<n;i++)
{
fscanf(f," %d",&a[i]);

printf(" %d",a[i]);
}

first=0;
last=n-1;
middle=(first+last)/2;

while(first<=last)
{
if(a[middle]<search){

first= middle+1;
middle=(first+last)/2;
}

else if(a[middle]==search)
{
printf("\n%d Element found at location %d \n", search, middle+1);
flag=1;
break;
}
else
{
last=middle-1;
middle=(first+last)/2;
}
}

if(flag==0)
printf("\n Not found");

 

return(0);
}

 

void bsearch(int a[11], int search)
{
int i, first, last, middle, n=10;

 

 

first=0;
last=n-1;
middle=(first+last)/2;

while(first<=last)
{
if(a[middle]<search)

first= middle+1;

else if(a[middle]==search)
{
printf("%d Element found at location %d \n", search, middle+1);
break;
}
else
{
last=middle-1;
middle=(first+last)/2;
}

if(first>last)
{
printf("Element not found %d is not present in the list\n", search);
//return 0;
}
}
}

