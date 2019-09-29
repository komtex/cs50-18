#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Initialize and store file name
    char *image = argv[1];

    // Accept only one command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(image, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", image);
        return 2;
    }

    // Initialize JPG identification search buffer to size of read in chunks
    // Using 'unsigned' for 0 to 255
    unsigned char buffer[512];

    // Initialize tracker variables
    int openFileTracker = 0;
    int jpegTracker = 0;

    // Initialize file name and img_file
    char filename[10];
    FILE *img_file;


    // Loop through reading 512 byte blocks of image file till you get to end of the file
    // ...Using fread's return value to designate if a complete block was returned or failed... eg EOF reached
    // ...Using while loop's expression boolean returning false to end the looping at EOF
    while (fread(&buffer, 512, 1, inptr))
    {
        // Check first 4 bytes of buffered chunk to see if it corrisponds to the start of a JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            // Yes...this is the start of a new JPEG
        {
            // Do we already have a JPEG file open?
            // If we have an open file
            if (openFileTracker)
            {
                // close the previously opened file
                fclose(img_file);

                // set openFileTracker as false (this is a safety)
                openFileTracker = 0;

                // create new file name
                sprintf(filename, "%03d.jpg", jpegTracker);

                // TEST file name output
                //eprintf("The name of the new file is %s\n", filename);

                // apply and open this new file
                img_file = fopen(filename, "a");

                // set openFileTracker to true
                openFileTracker = 1;

                // Increment our file naming tracker
                jpegTracker++;
            }

            // If we do NOT have an open file
            if (!openFileTracker)
            {
                // name a new file and open it
                sprintf(filename, "%03d.jpg", jpegTracker);
                img_file = fopen(filename, "w");

                // We now have an open file.
                openFileTracker = 1;

                jpegTracker++;
            }

            // write the buffer to the file
            fwrite(&buffer, 512, 1, img_file);
        }

        // No...this is not the start of a new JPEG
        else
        {
            if (openFileTracker)
            {
                // Write the block to the file
                fwrite(&buffer, 512, 1, img_file);
            }

            if (!openFileTracker)
            {
                // This simply does nothing since this block of 512 bytes can be discarded and we move back to top of the while loop.
            }
        }

    }

    // While loop terminated:  we have reached EOF
    // Close the initial image file
    fclose(inptr);

    // close any open jpeg file
    fclose(img_file);

    return 0;
}