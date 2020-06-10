#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Need to cast as float otherwise it's int / int division and you lose precision
            // Round goes to nearest int

            int average = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Changing pixel to sepia red

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else if (sepiaRed < 0)
            {
                image[i][j].rgbtRed = 0;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            // Changing pixel to sepia green

            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                image[i][j].rgbtGreen = 0;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            // Changing pixel to sepia blue

            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                image[i][j].rgbtBlue = 0;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            // Need to subtract j to move inwards
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the original array so that you can refer to the copy
    // This is necessary to not mess with the original array
    
    RGBTRIPLE copy[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    
    // Look at pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Cast as float for precision
            // Needs to be outside of 3x3 loop to keep proper count
            float totalred = 0;
            float totalgreen = 0;
            float totalblue = 0;
            int squares = 0;
                    
            // Build a 3x3 around that pixel
            for (int a = (i - 1); a <= (i + 1); a++)
            {
                for (int b = (j - 1); b <= (j + 1); b++)
                {
                    // Stay within bounds of original array
                    if (a >= 0 && b >= 0 && a <= height - 1 && b <= width - 1)
                    {
                        // Find color totals using the copied array
                        totalred += copy[a][b].rgbtRed;
                        totalgreen += copy[a][b].rgbtGreen;
                        totalblue += copy[a][b].rgbtBlue;
                        squares++;
                    }
                }
            }
            
            // Make original array to the average
            // Needs to be outside of 3x3 loop to keep proper count
            image[i][j].rgbtRed = round(totalred / squares);
            image[i][j].rgbtGreen = round(totalgreen / squares);
            image[i][j].rgbtBlue = round(totalblue / squares);
        }
    }
    return;
}
