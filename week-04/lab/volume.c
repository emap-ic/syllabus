// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
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

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Determine size (in bytes) of file, from beggining to en
    fseek(input, 0, SEEK_END); 
    long size = ftell(input); 

    // Come back with file pointer to the beggining
    fseek(input, 0, SEEK_SET); 

    // The number of bytes pairs after the header
    int numPairsBytes = size / sizeof(int16_t) - HEADER_SIZE;

    // Alloc memory to the buffer to read it at once
    int16_t *pairsBytes = (int16_t*)malloc(numPairsBytes * sizeof(int16_t));
    fread(pairsBytes, sizeof(int16_t), numPairsBytes, input);

    // Update volume by factor
    for(int i = 0; i < numPairsBytes; i++)
        pairsBytes[i] *= factor;

    // Write the up to date array to output file
    fwrite(pairsBytes, sizeof(int16_t), numPairsBytes, output);

    // Close files
    fclose(input);
    fclose(output);
}