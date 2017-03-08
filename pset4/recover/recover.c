#include <stdio.h>

#define MEMBLOCK 512
#define BUFFER_SIZE 4

int loadSignature (FILE *file, unsigned char buffer[], int size);
int isJpegSignature (unsigned char buffer[]);

int main (int argc, char *argv[])
{
  // validate argument count
  if (argc != 2)
  {
    fprintf(stderr, "Usage: ./recover image\n");
    return 1;
  }

  // open the source file
  FILE *sourceFile = fopen(argv[1], "r");

  // verify that the file is open
  if (sourceFile == NULL)
  {
    fprintf(stderr, "Could not open %s.\n", argv[1]);
    return 2;
  }

  // signature buffer
  unsigned char buffer[BUFFER_SIZE];

  // image buffer
  unsigned char imgBuffer[MEMBLOCK];

  // output file variables
  FILE *img = NULL;
  int fileCount = 0;
  char fileName[8];
  int fileOpen = 0;

  // analize the source file block by block of 512 bytes
  while (loadSignature(sourceFile, buffer, BUFFER_SIZE))
  {
    // check if this MEMBLOCK starts with a JPEG signature
    if (isJpegSignature(buffer))
    {
      // if a JPEG file was already open close it
      if (fileOpen)
      {
        fclose(img);
      }

      // generate file name and open it
      sprintf(fileName, "%03i.jpg", fileCount);
      img = fopen(fileName, "w");

      // update the state
      fileOpen = 1;
      fileCount++;
    }

    // if this MEMBLOCK is part of a JPEG
    if (fileOpen)
    {
      // write to the opened image file
      fread(imgBuffer, sizeof(unsigned char), MEMBLOCK, sourceFile);
      fwrite(imgBuffer, sizeof(unsigned char), MEMBLOCK, img);
    }
    else
    {
      // move the cursor to the next MEMBLOCK of the source file
      fseek(sourceFile, MEMBLOCK, SEEK_CUR);
    }
  }

  // close the files
  if (fileOpen)
  {
    fclose(img);
  }
  fclose(sourceFile);

  // success!
  return 0;
}


int loadSignature (FILE *file, unsigned char buffer[], int size)
{
  // load the buffer reading from a file
  if (fread(buffer, sizeof(unsigned char), size, file) == size)
  {
    // move back the cursor at the start of the MEMBLOCK
    fseek(file, -size, SEEK_CUR);
    return 1;
  }

  // buffer empty
  return 0;
}


int isJpegSignature (unsigned char buffer[])
{
  // detect if the values match the JPG signature
  return buffer[0] == 0xff && buffer[1] == 0xd8 &&
    buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}
