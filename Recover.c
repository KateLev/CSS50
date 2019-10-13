#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n = 0;
    int segment_count = 0;
    char *infile = argv[1]; //argv[1] is a name of camera's card
    FILE *inptr = fopen(infile, "r"); //we are opening the file. In this case it's card.raw

   //we are checking if the input file exists

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //we need a new char for each 512
    unsigned char* buffer=malloc(512);

    //we are starting to read infile and store information in container
    while (fread(buffer, 1, 512, inptr)) // because 1 block of 512 and when we finished there will no any blocks
    {

        segment_count+=1;
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]&0xf0) == 0xe0 )
        {
            n+=1;
        }


    }
    printf("We have %i jpeg files \n", n);
    printf("We have %i 512 blocks \n", segment_count);
    // close infile
    fclose(inptr);
    free(buffer);

}
