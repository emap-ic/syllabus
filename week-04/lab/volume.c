#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    // copy header from input file to output file

    uint8_t *header;
    header = malloc(HEADER_SIZE*sizeof(uint8_t));
    
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
    free(header);

    // copy the content applying the factor

    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input)){
      buffer *= factor;
      fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);    
}
