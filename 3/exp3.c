#include<stdio.h>
#include<pthread.h>
#define size 10

int a[size][size],b[size][size],c[size][size];

void *mul_thread(void *args)
{
  int row,col,*rcargs,i;
  int long return_val;
  
  rcargs=(int*)args;
  row=rcargs[0];
  col=rcargs[1];
  i=rcargs[2];
  return_val=a[row][i]*b[i][col];
  pthread_exit((void *)return_val);
}

void accept(int m[size][size],int row,int col)
{
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      scanf("%d",&m[i][j]);
    }
  }  
}

void display(int m[size][size],int row,int col)
{
  for(int i=0;i<row;i++)
  {
    printf("\n");
    for(int j=0;j<col;j++)
    {
      printf("%d\t",m[i][j]);
    }
  }  
}

int main()
{
  int rowa,rowb,cola,colb,i,k,j;
  int rcargs[3],*status;
  pthread_t p[size][size][size];
  
  printf("\n Enter no. of rows and columns of matrix A:");
  scanf("%d %d",&rowa,&cola);
  printf("\n Enter values:\n");
  accept(a,rowa,cola);
  
  printf("\n Enter no. of rows and columns of matrix B:");
  scanf("%d %d",&rowb,&colb);
  printf("\n Enter values:\n");
  accept(b,rowb,colb);
  if(cola==rowb)
  {
  for(i=0;i<rowa;i++)
  {
    for(j=0;j<colb;j++)
    {
      for(k=0;k<cola;k++)
      {
        rcargs[0]=i;
        rcargs[1]=j;
        rcargs[2]=k;
        pthread_create(&p[i][j][k],NULL,mul_thread,rcargs);
        pthread_join(p[i][j][k],(void **)&status);
        c[i][j]+=(long)status;
      }
    }
  }
  
  printf("\nMatrix A:\n");
  display(a,rowa,cola);
  
  printf("\nMatrix B:\n");
  display(b,rowb,colb);
  
  printf("\nMatrix A:\n");
  display(c,rowa,colb);
  }
  else printf("\n Multiplication not possible!");
  return 0;
}
