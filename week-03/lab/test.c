#include <stdio.h>
#include <stdlib.h>


int dup(int m)
{
    m = m + m;
    return m;
}


int main(int argc, char* argv[])
{
    int m = 30;
    printf("valor %i\n", m);
    printf("valor %i\n", dup(m));
    printf("valor %i\n", m);

}