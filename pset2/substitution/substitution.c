#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string encrypt(string str, string key);
bool validity(string str);

int main(int argc, string argv[])
{
    if (argc == 2) // If user has entered a single string for cipher key
    {
        if(validity(argv[1])) // If user entered key is valid
        {
            string plaintext = get_string("plaintext: "); // Prompting user for cipher key
            printf("ciphertext: %s\n" , encrypt(plaintext, argv[1]));
            return 0;
        }
        else // If user has entered has not entered exactly 26 unique characters for cipher key
            printf("Key must contain 26 characters.\n");
        return 1;
    }
    else // If user has entered more than one string for cipher key
        printf("Usage : ./substitution key\n");
    return 1;
}

string encrypt(string str, string key)
{
    char ch;
    for(int i = 0, n = strlen(str); i < n; i++)
    {
        ch = str[i];
        if(isalpha(ch))
        {
            if(islower(ch)) // If character is in lowercase
                str[i] = tolower(key[ch - 'a']);
            else // If character is in uppercase
                str[i] = toupper(key[ch - 'A']);
        }
    }
    return str;
}

bool validity(string str)
{
    if(strlen(str) == 26) // If key string length is 26characters
    {
        int count[26]; // Stores frequency of each alphabet in key
        for(int i = 0; i < 26; i++)
        {
            count[i] = 0; // Initializes frequency of each alphabet with zero
            if(!isalpha(str[i])) // If user enter non-alphabetic character in key
                return false;
        }
        for(int i = 0; i < 26; i++)
            count[tolower(str[i]) - 'a']++;
        for(int i = 0; i < 26; i++)
            if(count[i] != 1) // If each alphabet in key has not appeared exactly once
                return false;
        return true;
    }
    return false; // If key length is not 26 characters
}