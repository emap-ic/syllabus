#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

/* ambas as funcoes recebem 'int *numbers' que internamente deve ser
   tratado na função como numbers sendo um array de tamanho 'size'. O
   efeito desejado é que o array passado será alterado para função
   embora nenhum valor seja explicitamente retornado por elas. */

void bubble(int *numbers, int size)
{
  bool changed;
  do
  {
    changed = false;
    for(int i = 0; i < size - 1; i++)
    {
      if(numbers[i] > numbers[i+1])
      {
        int aux = numbers[i];
        numbers[i] = numbers[i+1];
        numbers[i+1] = aux;
        changed = true;
      }
    }
  } while(changed);
}

void selection(int *numbers, int size)
{
  for (int i = 0, min = i; i < size; i++)
  {
    min = i;
    for (int j = i + 1; j < size; j++)
    {
      if (numbers[j] < numbers[min])
      {
        min = j;
      }
    }
    int aux = numbers[i];
    numbers[i] = numbers[min];
    numbers[min] = aux;
  }
}


/* Vide
   http://algorithmics.lsi.upc.edu/docs/Dasgupta-Papadimitriou-Vazirani.pdf
   pagina 56 (seçao 2.3). Para não usar ponteiros, operações feitas
   'in-place'. Two subarrays of arr[]: first is arr[l..m] and the
   second is arr[m+1..r] */

void merge(int *arr, int start, int mid, int end)
{
    int start2 = mid + 1;

    // if it is already sorted
    if (arr[mid] <= arr[start2]) {
        return;
    }

    // two pointers for both subarrays
    while (start <= mid && start2 <= end) {

        // if first element is in right place
        if (arr[start] <= arr[start2]) {
            start++;
        }
        else {
            int value = arr[start2];
            int index = start2;

            // shift all the elements between element 1 element 2,
            // right by 1.
            while (index != start) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;

            // update all the pointers
            start++;
            mid++;
            start2++;
        }
    }
}

void merge_sort(int *numbers, int l, int r)
{
    if (l < r) {
        int m = (l + r) / 2;

        merge_sort(numbers, l, m);
        merge_sort(numbers, m + 1, r);

        merge(numbers, l, m, r);
    }
}

// utilities

void print_array(int *numbers, int size)
{
  for(int i = 0; i < size; i++)
  {
    printf("%d\n", numbers[i]);
  }
}

void usage()
{
  printf("\n\tUsage ./sort [b|s|m] FILE\n\n");
}



int main(int argc, char* argv[])
{

  if(argc < 3)
  {
    printf("Error: wrong number of arguments.\n");
    usage();
    return 1;
  }

  FILE* fp = NULL;
  fp = fopen(argv[2], "r");
  if (fp == NULL)
    {
      printf("Error: can't open the file %s.\n", argv[2]);
      return 1;
    }

  // getting the number of elements from the first line
  char *line = NULL;
  int N;
  fscanf(fp, "%i", &N);

  // creating the array and reading the file
  int numbers[N];

  for(int i = 0; i < N; i++)
  {
    int r = fscanf(fp, "%i", &numbers[i]);
    if(r == EOF)
    {
      printf("Error: missing numbers according to the header!\n");
      return 1;
    }
  }

  /* antes da próxima linha, deve acrescentar um código que verifica o
     valor do segundo parâmetro passado para o programa escolhe a
     função de sort adequada. Ambas as funções irão modificar o
     parâmetro passado mas não retornar nada. A função 'print_array'
     então irá imprimir o array ordenado. */

  if(strcmp(argv[1], "b") == 0)
    bubble(numbers, N);
  else if(strcmp(argv[1], "s") == 0)
    selection(numbers, N);
  else if(strcmp(argv[1], "m") == 0)
    merge_sort(numbers, 0, N - 1);
  else
  {
    usage();
    return 1;
  }

  print_array(numbers, N);
  fclose(fp);
  return 0;
}

