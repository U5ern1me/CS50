#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) // For each pixel
        {
            image[i][j].rgbtBlue = (BYTE) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][j].rgbtBlue;
        }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp; // Stores RGBTRIPLE values temporarily to swap values in 2 variables
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width / 2; j++)
        {
            tmp.rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tmp.rgbtBlue;
            
            tmp.rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tmp.rgbtGreen;
            
            tmp.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tmp.rgbtRed;
        }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float count; // To keep count of number of all pixels within a row or column
    WORD sum[3]; // To compute sum of rgb values of neighbouring pixels
    RGBTRIPLE copy[height][width]; // To store blurred image
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            count = 0.0;                // Initializing
            for (int p = 0; p < 3; p++) // values to zero
                sum[p] = 0;             // for each pixel
            for (int p = i - 1; p <= i + 1; p++)
                for (int q = j - 1; q <= j + 1; q++)
                    if (p >= 0 && p < height && q >= 0 && q < width) // If pixel is not outside image
                        {
                            sum[0] += image[p][q].rgbtBlue;
                            sum[1] += image[p][q].rgbtGreen;
                            sum[2] += image[p][q].rgbtRed;
                            count++;
                        }
            copy[i][j].rgbtBlue = (BYTE) round(sum[0] / count);
            copy[i][j].rgbtGreen = (BYTE) round(sum[1] / count);
            copy[i][j].rgbtRed = (BYTE) round(sum[2] / count);
        }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int sum[3][2]; // To compute and store Gx and Gy
    RGBTRIPLE copy[height][width]; // To store edge filtered image
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) // For each pixel
        {
            for (int p = 0; p < 3; p++)
                for (int q = 0; q < 2; q++)
                    sum[p][q] = 0; // Initializing to zero for each pixel
            for (int p = i - 1; p <= i + 1; p++)
                for (int q = j - 1; q <= j + 1; q++)
                    if (p >= 0 && p < height && q >= 0 && q < width) // If pixel is not outside of image
                    {
                        sum[0][0] += (q - j) * image[p][q].rgbtBlue;
                        sum[1][0] += (q - j) * image[p][q].rgbtGreen;
                        sum[2][0] += (q - j) * image[p][q].rgbtRed;
                        
                        sum[0][1] += (p - i) * image[p][q].rgbtBlue;
                        sum[1][1] += (p - i) * image[p][q].rgbtGreen;
                        sum[2][1] += (p - i) * image[p][q].rgbtRed;
                        
                        if (p == i)
                        {
                            sum[0][0] += (q - j) * image[p][q].rgbtBlue;
                            sum[1][0] += (q - j) * image[p][q].rgbtGreen;
                            sum[2][0] += (q - j) * image[p][q].rgbtRed;
                        }
                        if (q == j)
                        {
                            sum[0][1] += (p - i) * image[p][q].rgbtBlue;
                            sum[1][1] += (p - i) * image[p][q].rgbtGreen;
                            sum[2][1] += (p - i) * image[p][q].rgbtRed;
                        }
                    }
            for (int p = 0; p < 3; p++)
            {
                sum[p][0] = (int) round(pow((sum[p][0] * sum[p][0] + sum[p][1] * sum[p][1]),0.5));
                if (sum[p][0] > 255) 
                    sum[p][0] = 255;
            }
            copy[i][j].rgbtBlue = (BYTE) sum[0][0];
            copy[i][j].rgbtGreen = (BYTE) sum[1][0];
            copy[i][j].rgbtRed = (BYTE) sum[2][0]; 
        }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
}
