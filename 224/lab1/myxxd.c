#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits)
{
  if (argc > 2)
  {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0))
  {
    *bits = TRUE;
  }
  else
  {
    *bits = FALSE;
  }

  return stdin;
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size)
{
  const int BIT_COUNT = 16;
  const int BYTE_SIZE = 2;
  const int MISSING_BYTES = BIT_COUNT - size;
  const float SPACE_PER_BYTE = 1;

  // Print data, spacing every 2 bytes
  for (int i = 0; i < size; i++)
  {
    if (i % 2 == 0)
    {
      printf(" ");
    }
    printf("%02x", data[i]);
  }

  // Print trailing space on last line
  if (MISSING_BYTES != 0)
  {
    for (int i = 0; i < ((BYTE_SIZE * MISSING_BYTES) + (int)(SPACE_PER_BYTE * MISSING_BYTES / 2)); i++)
    {
      printf(" ");
    }
  }
}

/**
 * Converts a hexadecimal number into a string of binary digits
 * @param hex the hexadecimal value
 * @param returnVal a nine-element array/8 char string
 **/
void printHexAsBinary(int hex)
{
  const int BYTE_SIZE = 8;
  const char ASCII_ZERO = 48;
  const char ASCII_ONE = 49;
  char returnVal[BYTE_SIZE];
  returnVal[BYTE_SIZE] = 0;

  for (int i = BYTE_SIZE - 1; i >= 0; i--)
  {
    const int bit = hex % 2;
    if (bit)
    {
      returnVal[i] = ASCII_ONE;
    }
    else
    {
      returnVal[i] = ASCII_ZERO;
    }

    hex /= 2;
  }
  printf("%s", returnVal);
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsBits(unsigned char *data, size_t size)
{
  const int BIT_COUNT = 6;
  const int BIT_SIZE = 8;
  const int MISSING_BITS = BIT_COUNT - size;
  const int SPACE_PER_BYTE = 1;

  // Print data, spacing every 2 bytes for (int i = 0; i < size; i++)
  for (int i = 0; i < size; i++)
  {
    printf(" ");
    printHexAsBinary(data[i]);
  }

  // Print trailing space on last line
  if (MISSING_BITS != 0)
  {
    for (int i = 0; i < ((BIT_SIZE + SPACE_PER_BYTE) * MISSING_BITS); i++)
    {
      printf(" ");
    }
  }
}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%c", data[i]);
  }
}

void readAndPrintInputAsHex(FILE *input)
{
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0)
  {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input)
{
  unsigned char data[6];
  int numBytesRead = fread(data, 1, 6, input);
  unsigned int offset = 0;
  while (numBytesRead != 0)
  {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsBits(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 6, input);
  }
}

int main(int argc, char **argv)
{
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE)
  {
    readAndPrintInputAsHex(input);
  }
  else
  {
    readAndPrintInputAsBits(input);
  }
  return 0;
}
