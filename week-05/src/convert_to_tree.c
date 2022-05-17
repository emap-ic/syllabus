#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct node
{

    int number;
    struct node *left;
    struct node *right;
}
node;

node *convert_array_to_tree(int *linear)
{
    node *tree = NULL;
    node *temp = tree;
    
    //descobrir tamanho do array
    int lenght = 0;
    for (int j = 0; linear[j] != '\0';j++)
    {
        lenght++;
    }

    for (int i = 0; i < lenght; i++)
    {
        //primeiro item da lista será o primeiro ramo da árvore
        if (i == 0)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                free(n);
                return NULL;
            }
            n-> number = linear[0];
            n -> right = NULL;
            n -> left = NULL;
            tree = n;
        }
        else
        {
            int cont = 0;
            while (true)
            {
                if (cont == 0)
                {
                    temp = tree;
                }
                
                //evitar loop infinito se tiver números que se repetem no array
                if (linear[i] == temp ->number)
                {
                    printf("ERRO. Números repetidos no array\n");
                    return NULL;
                }        
                
                if (linear[i] < temp -> number)
                {
                    if (temp -> left == NULL)
                    {
                        node *n = malloc(sizeof(node));
                        if (n == NULL)
                        {
                            free(n);
                            return NULL;
                        }
                        n-> number = linear[i];
                        n -> right = NULL;
                        n -> left = NULL;
                        temp -> left = n;
                        break;
                    }

                    else
                    {
                        temp = temp -> left;
                    }
                }

                else if (linear[i] > temp -> number)
                {
                    if (temp -> right == NULL)
                    {
                        node *n = malloc(sizeof(node));
                        if (n == NULL)
                        {
                            free(n);
                            return NULL;
                        }
                        n-> number = linear[i];
                        n -> right = NULL;
                        n -> left = NULL;
                        temp -> right = n;
                        break;
                    }

                    else
                    {
                        temp = temp -> right;
                    }
                }
                cont++;
            }

        }
    }
    return tree;
}
