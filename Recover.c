#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "The wrong command. Usage: ./recover infile\n");
        return 1;
    }

    int n = 0;
    int new_file = 0;
    char *infile = argv[1]; //argv[1] is a name of camera's card

    FILE *outptr;
    FILE *inptr = fopen(infile, "r"); //we are opening the file. In this case it's card.raw

    //we are checking if the input file exists

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //we need a new char for each 512
    unsigned char *buffer = malloc(512); //here can be unsigned char buffer [512];

    //we are starting to read infile and store information in container
    while (fread(buffer, 1, 512, inptr)) // because 1 block of 512 and when we finished there will no any blocks
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // initial symbols of jpg
        {
            char outfile [8];
            sprintf(outfile, "%03i.jpg", n);    //I have n as a counter of the files and I can use it to create a file name

            if (new_file == 1) //if new_file=0, it is the first our jpg file
            {
                fclose(outptr); //close the current file
            }

            else
            {
                new_file = 1;
            }

            outptr = fopen(outfile, "w");
            n += 1;

        }
        if (n != 0)  //because if n=0, the we did not find the initial symbols yet
        {
            fwrite(buffer, 1, 512, outptr);
        }

    }
//    printf("We have %i jpeg files \n", n);
//    printf("We have %i 512 blocks \n", segment_count);

    fclose(inptr);  // close infile
    free(buffer);

}
