#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *name(int num);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid input. Usage: ./recover image\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r"), *file = fopen("000.jpg", "w");
    if (input == NULL || file == NULL)
    {
        printf("Unable to open file.\n");
        return 1;
    }
    typedef uint8_t byte;
    byte buffer[512];
    char name[8]; // Stores names of jpeg files
    int count = 0; // Stores count of jpeg files
    while (fread(buffer, sizeof(byte), 512, input))
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && buffer[3] / 16 == 14) // If conditions of a jpeg file are satisfied
            break;
    fwrite(buffer, sizeof(byte), 512, file); // Writes in 000.jpg
    while (fread(buffer, sizeof(byte), 512, input))
    {

        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && buffer[3] / 16 == 14) // If start of new jpeg file
        {
            fclose(file); // Closes previously open jpeg file
            if (count < 9) // If jpeg file name has a single digit
                sprintf(name, "00%i.jpg", ++count);
            else // If jpeg file name has double digits
                sprintf(name, "0%i.jpg", ++count);
            file = fopen(name, "w"); // Opens new jpeg file to write into
            if (file == NULL)
            {
                printf("Unable to open file.\n");
                return 1;
            }
        }
        fwrite(buffer, sizeof(byte), 512, file);
    }
    fclose(file);
    fclose(input);
    return 0; 
}