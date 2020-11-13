#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float grayvalue ;

    for (int i=0; i < height; i++)
    {
        for(int j=0; j < width; j++)
        {
        grayvalue = round((image[i][j].rgbtRed +image[i][j].rgbtBlue +image[i][j].rgbtGreen)/3 );

        image[i][j].rgbtRed= grayvalue;
        image[i][j].rgbtGreen=grayvalue;
        image[i][j].rgbtBlue=grayvalue;
    }
    }
}
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
   int sepiaRed;
   int sepiaGreen;
   int sepiaBlue;
   for (int i=0; i<height; i++)
   {
       for (int j=0; j<width;j++)
       {
             sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
             sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
             sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            image[i][j].rgbtRed=sepiaRed;
            image[i][j].rgbtGreen=sepiaGreen;
            image[i][j].rgbtBlue=sepiaBlue;
       }
    }
   }



// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp [3];
    for (int i =0; i<height; i++)
    {
        for (int j =0; j<width/2; j++)
        {
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtRed = temp[2];
        }
    }
}
// Blur image

   void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumofBlue;
    int sumofGreen;
    int sumofRed;
    float counter;
    
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumofBlue = 0;
            sumofGreen = 0;
            sumofRed = 0;
            counter = 0.00;

            
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumofBlue += image[j + k][i + h].rgbtBlue;
                    sumofGreen += image[j + k][i + h].rgbtGreen;
                    sumofRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            
            temp[j][i].rgbtBlue = round(sumofBlue / counter);
            temp[j][i].rgbtGreen = round(sumofGreen / counter);
            temp[j][i].rgbtRed = round(sumofRed / counter);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}
