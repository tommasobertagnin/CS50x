/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize scale infile outfile\n");
        return 1;
    }

    // store and validate scale value
    int scale = atoi(argv[1]);
    if (scale < 1 || scale > 100)
    {
        fprintf(stderr, "Scale should be a value between 1 and 100\n");
        return 1;
    }

    // store file names
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

    // read infile's BITMAPFILEHEADER and make a copy for the out file
    BITMAPFILEHEADER bf, outBf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    outBf = bf;

    // read infile's BITMAPINFOHEADER and make a copy for the out file
    BITMAPINFOHEADER bi, outBi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    outBi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // update the BITMAPINFOHEADER for the resized file
    outBi.biWidth  = bi.biWidth  * scale;
    outBi.biHeight = bi.biHeight * scale;

    // determine padding for output file scanlines
    int outPadding = (4 - (outBi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    outBi.biSizeImage = (sizeof(RGBTRIPLE) * outBi.biWidth + outPadding) * abs(outBi.biHeight);

    // update the BITMAPFILEHEADER for the resized file
    outBf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + outBi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&outBf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outBi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for input file scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // repeat for every line of the output file
        for (int sh = 0; sh < scale; sh++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile (repeat according to scale)
                for (int sw = 0; sw < scale; sw++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add padding to the out file
            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }

            // move back the cursor
            fseek(inptr, -1 * ((int) sizeof(RGBTRIPLE) * bi.biWidth), SEEK_CUR);
        }

        // skip over scanline for the next iteration
        fseek(inptr, ((int) sizeof(RGBTRIPLE) * bi.biWidth) + padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
