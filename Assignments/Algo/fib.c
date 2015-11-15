#include<stdio.h>
#include<time.h>

int fibRec(int n);
// int fibLoop(int n);
// int fib_t(int n);
// int fib_t_r(int n, int a, int b);

int main()
{

	clock_t begin,end;
	// FILE *fp;
	// fp = fopen("list.txt", "w");

  	for(int n = 1; n < 46; n++){
  	
  		double time_spent=0;

  		begin = clock();
  		fibRec(n);
  		end = clock();

  		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  		printf("%i %f\n",n,time_spent);
  	}

  	return 0;
}

int fibRec(int n)
{
	if(n==0||n==1)
	{
	  	return n;
	}

	return fibRec(n-1)+fibRec(n-2);

}

// int fibLoop(int n)
// {

//   if(n<2)
//      return n;
  
//   int last=1;
//   int old_last=0;

//   int i;

//   for(i=2;i<=n;i++)
//       {
//         int temp=last;
//         last=last+old_last;
//         old_last=temp;
//       }

//   return last;
  
// }

// int fib_t_r(int n, int a, int b)
// {
//    if(n==0)
//      return a;
//    if(n==1)
//      return b;
//    if(n==2)
//      return a+b;
     
//    return fib_t_r(n-1,b,a+b);

// }

// int fib_t(int n)
// {
//   return fib_t_r(n,0,1);
// }