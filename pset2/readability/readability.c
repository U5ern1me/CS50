#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    string text = get_string("Text: "); // Prompt user to enter text
    int l = count_letters(text), s = count_sentences(text), w = count_words(text);
    float index = 0.0588 * (100.0*l / w) - 0.296 * (100.0*s / w) - 15.8; // Computinng rounded value of reading index
    printf("%i letter(s)\n" , l);
    printf("%i word(s)\n" , w);
    printf("%i sentences(s)\n" , s);
    if(index < 1)
        printf("Before Grade 1\n");
    else if(index > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n" , (int)round(index)); // Prints out truncated rounded value of index
}

int count_letters(string s)
{
    int count = 0; // Stores number of letters
    for(int i = 0, n = strlen(s); i < n; i++)
        if(isalpha(s[i]))
            count++;
    return count;
}

int count_words(string s)
{
    int count = 1; // Stores number of words, by keeping track of number of spaces
    for(int i = 0, n = strlen(s); i < n; i++)
        if(isspace(s[i])) // n spaces = n + 1 words
            count++;
    return count;
}

int count_sentences(string s)
{
    int count = 0; // Stores number of sentences by keeping track of punctuation
    for(int i = 0, n = strlen(s); i < n; i++)
        switch(s[i])
        {
            case '.':
            case '?':
            case '!':
                count++;
        }
    return count;
}
