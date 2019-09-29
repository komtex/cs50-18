#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(int argc, char* argv[])
{
    // remember filenames
    char* infile = "card.raw";

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    unsigned char block[512];

    int imagesRecovered = 0;

    bool jpegStarted = false;

    // open output file
    FILE* outptr;
    while(fread(block, 512, 1, inptr) != 0){

        //printf("%u\n", (int) block[0]);
        if ((int) block[0] == 255 && (int) block[1] == 216 && (int) block[2] == 255 && ((int) block[3] == 224 || (int) block[3] == 225))
        {
            if (jpegStarted)
            {
                fclose(outptr);
            }else{
                jpegStarted = true;
            }

            char fileName[4];
            if (imagesRecovered < 10)
            {
                sprintf(fileName, "00%i.jpg", imagesRecovered);
            }
            else
            {
                sprintf(fileName, "0%i.jpg", imagesRecovered);
            }

            outptr = fopen(fileName, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", fileName);
                return 3;
            }


            imagesRecovered++;

        }
        if (jpegStarted)
        {
            fwrite(&block, 512, 1, outptr);
        }
    }

    fclose(outptr);

    fclose(inptr);
}