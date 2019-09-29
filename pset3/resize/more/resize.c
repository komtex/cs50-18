// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr,"Usage: ./resize f  infile outfile\n");
        return 1;
    }
     // retrieve the scaling az float
     double f = atof(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
 // determine padding for scanlines images we are reading from
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //array to store pixels of reading image
    RGBTRIPLE image[bi.biWidth][abs(bi.biHeight)];

     // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store it in the array
            image[j][i] = triple;
        }
           // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

      //change the width & haight to suit new image
      bi.biWidth *= f;
      bi.biHeight *= f;

      //recalculate the padding of changed images
      padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

      //calculate the number of bites in non-header part of the outimage
      bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);

      //calculate the total number of bites
      bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //writing the changed image
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)

        {
            for(int j = 0; j < bi.biWidth; j++)
            {
                RGBTRIPLE triple;
                //use the f factor to find pixel should be placed
                triple = image[(int) (j / f)][(int) (i / f)];
                //prinf("(%i, %i, %i)\n", triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);
                //write the pixel to the file
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
               // then add it to outfile
                for (int k = 0; k < padding; k++)
                  {
                    fputc(0x00, outptr);
                  }

        }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
