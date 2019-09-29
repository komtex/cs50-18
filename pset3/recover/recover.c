#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>
int main(int argc, char *argv[])
{
    char *infile = argv[1];
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./recover image\n");
        return 1;
    }

    //open memory card
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    unsigned char buffer[512];
    bool openFile = false;
    int jpegStart = 0;
    char filename [10];
    FILE *img_file;
    while (fread(&buffer, 512, 1, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            //yes started jpeg
        {
            if (openFile)
            {
                //close prev. opened file
                fclose(img_file);
                //set to false
                openFile = false;
                sprintf(filename, "%03d.jpg", jpegStart);
                img_file = fopen(filename, "a");
                openFile = true;
                jpegStart ++;
            }
            //do not have an open file
            if (!openFile)
            {
                //name a new one
                sprintf(filename, "%03d.jpg", jpegStart);
                img_file = fopen(filename, "w");
                openFile = true;
                jpegStart ++;
            }
            fwrite(&buffer, 512, 1, img_file);
        }
        else
        {
            if (openFile)
            {
                fwrite(&buffer, 512, 1, img_file);
            }
            if (!openFile)
            {
                //does nothing
            }
        }

    }

    fclose(inptr);
    fclose(img_file);

    return 0;
}
