#include <cs50.h>
#include <stdio.h>
bool checksum(long n);
bool mastercard(long n);
int main(void)
{
    long num = get_long("Enter Credit Card number.\n"); // Accept credit card number from user in variable num
    if (checksum(num)) // If Luhn's checksum algorithm validates card number
    {
        if (num / 10000000000000 == 34 || num / 10000000000000 == 37) // If num has 15 digits and starts with 35 or 37
            printf("AMEX\n");
        else if (num / 1000000000000 == 4 || num / 1000000000000000 == 4) // If num has 13 or 16 digits and starts with 4
            printf("VISA\n");
        else if (mastercard(num))
            printf("MASTERCARD\n");
        else
            printf("INVALID\n");
    }
    else // If Luhn's checksum algorithm invalidates card number 
        printf("INVALID\n");
}
bool checksum(long n)
{
    int sum = 0, digit;
    while (n > 0)
    {   
        digit = n / 10 % 10 * 2; // Stores twice the value of the hunderedth's digit of num
    
        sum += digit % 10 + digit / 10 + n % 10; // Stores sum of odd placed digits and sum of digits of twice of even placed digits
        n /= 100; // Removes last two digits of num
    }
    if (sum % 10 == 0) // If sum ends with zero
        return true;
    else 
        return false;
}
bool mastercard(long n)
{   
    for (int i = 1; i <= 5; i++)
        if (n / 100000000000000 == 50 + i) // If num has 16 digits and starts with 51, 52, 53, 54 or 55
            return true;
    return false;
}