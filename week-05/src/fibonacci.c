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


long fib3(int n)
{
  long anteriores[] = {0, 1};
    
  if (n < 2)
    return anteriores[n];
    
  do {
    long next = anteriores[0] + anteriores[1];
    anteriores[0] = anteriores[1];
    anteriores[1] = next;
    n--;
    // printf("> debug i:%i next:%ld 0:%ld 1:%ld \n", n, next, anteriores[0], anteriores[1]);
  } while (n > 1);

  return anteriores[1];
}



int main(int argc, char *argv[])
{
  if(argc < 2)
    exit(1);
  
  long x = atol(argv[1]);
  
  // printf("%ld %ld\n", fib2(x), fib3(x));
  printf("%ld\n", fib3(x));
  exit(0);
}
