#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Given - a byte of data
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // If not a file or the arg count != 2, return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open card.raw and open it in FILE *card
    FILE *card = fopen(argv[1], "r");

    if (!card)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // You don't need malloc because you know how big everything is
    // Need a temporary buffer to write to
    // Need a place to store the filename (000.jpg\0 = 8 bytes)
    // jpeg_counter is for the file number "00i"
    // FILE *img is a place for the 00i.jpg to go to. Set to NULL
    BYTE buffer[512];
    char filename[8];
    int jpeg_counter = 0;
    FILE *img = NULL;

    // fread() == 1 because it returns the number of items read (512 bytes of 1 block)
    // Keep reading until you can't read 512 bytes anymore
    while (fread(buffer, 512, 1, card) == 1)
    {
        // If you find a jpg
        // Note: if you can't find a jpg, it'll just continue the while loop
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
        {
            // If your FIRST jpg
            if (jpeg_counter == 0)
            {
                // Make the file name; open it; increase the counter; write; WHILE LOOP WILL GO AHEAD WITH NEXT BLOCK
                // Notice the i, jpeg_counter = 00i.jpg
                sprintf(filename, "%03i.jpg", jpeg_counter);
                img = fopen(filename, "w");
                jpeg_counter++;
                fwrite(buffer, 512, 1, img);
            }
            // If you find the tag, but it's not your first jpg
            else
            {
                // Close the previous img, open a new one, repeat
                fclose(img);
                sprintf(filename, "%03i.jpg", jpeg_counter);
                img = fopen(filename, "w");
                jpeg_counter++;
                fwrite(buffer, 512, 1, img);
            }
        }
        // If not your first jpg, keep writing to the file until you encounter the jpg tags again
        else if (jpeg_counter >= 1)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(card);
}