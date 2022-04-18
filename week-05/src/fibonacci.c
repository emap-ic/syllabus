#include <stdio.h>
#include <stdlib.h>


long fib1(long x)
{
  if(x == 0) return 0;
  if(x == 1) return 1;

  return fib1(x - 1) + fib1(x - 2);
}

long fib2_aux(long x, long a, long b)
{
  if(x == 0)
    return a;

  return fib2_aux(x - 1, b, a + b);
}

long fib2(long x)
{
  return fib2_aux(x, 0, 1);
}

int main(int argc, char *argv[])
{
  if(argc < 2)
    exit(1);
  
  long x = atol(argv[1]);
  
  printf("%ld\n", fib2(x));
  exit(0);
}
