#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    
    //Promt user for input.
    do
        height = get_int("Enter height of pyramid : \n");
    while ( height < 1 || height > 8);
    
    for (int i = 1; i <= height; i++)
    {
        //Print spaces before pyramid's left triangle
        for (int j = height; j > i; j--)
            printf(" ");
            
        //Print pyramid's left triangle
        for (int j = 1; j <= i; j++)
            printf("#");
            
        //Print whitespace between the two triangles in the pyramid
        printf("  ");
        
        //Print pyramid's right triangle
        for (int j = 1; j <= i; j++)
            printf("#");
            
        //move cursor to next line
        printf("\n");
    }
}