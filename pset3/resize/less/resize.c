// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n  infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile =argv[3];
    if(n<1||n>=100)
    {
      fprintf(stderr, "resize n must be  positive between 1 and 100");
      return 1;
    }
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
      // Declare infile's and outfile's header files
    BITMAPFILEHEADER in_bf;
    BITMAPINFOHEADER in_bi;
    BITMAPFILEHEADER out_bf;
    BITMAPINFOHEADER out_bi;
    // read infile's BITMAPFILEHEADER and BITMAPINFOHEADER
    fread(&in_bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&in_bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (in_bf.bfType != 0x4d42 || in_bf.bfOffBits != 54 || in_bi.biSize != 40 ||
       in_bi.biBitCount != 24 || in_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    out_bf = in_bf;
    out_bi = in_bi;
    //change outfile's info header
     out_bi.biWidth = in_bi.biWidth * n;
     out_bi.biHeight = in_bi.biHeight * n;
     //calc infile and outfile padding
     int in_padding = (4 - (in_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     int out_padding = (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     //modify biSizeImage in outfile's info header
     out_bi.biSizeImage = (out_bi.biWidth * sizeof(RGBTRIPLE) + out_padding) * abs(out_bi.biHeight);
     //modify bfSize in outfile's  file header
     out_bf.bfSize = out_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER and BITMAPFILEINFOHEADER values for outfile
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
     //write resize data to the outfile


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(in_bi.biHeight); i < biHeight; i++)
    {
        //vertical resizing write each line n times
        for(int v=0; v < n; v++)
        {
        // iterate over pixels in scanline
         for (int j = 0; j < in_bi.biWidth; j++)
           {
            // temporary storage
            RGBTRIPLE triple;

              // read RGB triple from infile
              fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
              //horizontal resizing, write RGB triple to outfile
              for (int h=0; h < n; h++)
              {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
              }
           }

                  // skip over padding, if any
                fseek(inptr, in_padding, SEEK_CUR);

                  // then add it to outfile
              for (int k = 0; k < out_padding; k++)
               {
                 fputc(0x00, outptr);
               }
               //move pointer back to the beginning of the scan line
               fseek(inptr, -((in_bi.biWidth * sizeof(RGBTRIPLE)) + in_padding), SEEK_CUR);
        }

               fseek(inptr, ((in_bi.biWidth * sizeof(RGBTRIPLE)) + in_padding), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
