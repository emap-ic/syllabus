#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

/* ambas as funcoes recebem 'int *numbers' que internamente deve ser
   tratado na função como numbers sendo um array de tamanho 'size'. O
   efeito desejado é que o array passado será alterado para função
   embora nenhum valor seja explicitamente retornado por elas. */

void selection(int *numbers, int size);
void bubble(int *numbers, int size);


/* DESAFIO! Tentar implementar a função merge sort. Vide
   http://algorithmics.lsi.upc.edu/docs/Dasgupta-Papadimitriou-Vazirani.pdf
   pagina 56 (seçao 2.3) */

void merge(int *numbers, int size);

void print_array(int *numbers, int size)
{
  for(int i = 0; i < size; i++)
  {
    printf("%d\n", numbers[i]);
  }
}

void usage()
{
  printf("\n\tUsage ./sort [b|s] FILE\n\n");
}

int main(int argc, char* argv[])
{

  if(argc < 3)
  {
    printf("Error: wrong number of arguments.\n");
    usage();
    return 1;
  }

  if(strcmp(argv[1],"b") != 0 && strcmp(argv[1],"s") != 0)
  {
    printf("Error: second argument need to be 'b' or 's'\n");
    usage();
    return 1;
  }

  FILE* fp = NULL;
  fp = fopen(argv[2], "r");
  if (fp == NULL)
    {
      printf("Error ao abrir o arquivo %s.\n", argv[2]);
      return 1;
    }

  // getting the number of elements from the first line
  char *line = NULL;
  size_t len = 0;
  getline(&line, &len, fp);
  int N = atoi(line);

  // creating the array and reading the file
  int numbers[N];

  for(int i = 0; i < N; i++)
  {
    int r = getline(&line, &len, fp);
    if(r == -1)
    {
      printf("Error: missing numbers according to the header!");
      return 1;
    }
    numbers[i] = atoi(line);
  }

  /* antes da próxima linha, deve acrescentar um código que verifica o
     valor do segundo parâmetro passado para o programa escolhe a
     função de sort adequada. Ambas as funções irão modificar o
     parâmetro passado mas não retornar nada. A função 'print_array'
     então irá imprimir o array ordenado. */
  
  if(strcmp(argv[1], "b") == 0)
    bubble(numbers, N);
  else
    selection(numbers, N);

  print_array(numbers, N);

  fclose(fp);
  return 0;
}

void bubble(int *numbers, int size){

  for(int j = 0; j < size; j++){
    for(int i = 0; i < size - 1; i++){
      if(numbers[i] > numbers[i+1]){
        int aux = numbers[i];
        numbers[i] = numbers[i+1];
        numbers[i+1] = aux;
      }
    }
  }
}

void selection(int *numbers, int size){

  int i, j, indice_minimo;
  for (i = 0; i < size; i++) {
    for (j = i, indice_minimo = i; j < size; j++) {
      if (numbers[j] < numbers[indice_minimo]) {
        indice_minimo = j;
      }
    }
    int aux = numbers[i];
    numbers[i] = numbers[indice_minimo];
    numbers[indice_minimo] = aux;
  }
}
