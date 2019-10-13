#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n = 0;
    char *infile = argv[1]; //argv[1] is a name of camera's card
    FILE *inptr = fopen(infile, "r"); //we are opening the file. In this case it's card.raw

   //we are checking if the input file exists

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //we need a new char for each 512
    char *container [512];
    int buffer[512];

    //we are starting to read infile and store information in container
    while (fread(container, 1, 512, inptr)) // because 1 block of 512 and when we finished there will no any blocks
    {
        for (int i = 0; i < 3; i++)
        {
            buffer[i] = atof (container[i]);

        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]&0xf0) == 0xe0 )
        {
            n+=1;
        }

    }
    printf("We have %i jpeg files \n", n);

    // close infile
    fclose(inptr);
    free (container);
    free (buffer);
}
