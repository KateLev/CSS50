#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card_number = get_long("Number: ");    
    int checker = 0;
    float first_digit = card_number * 100;
    int sum = 0, sum2 = 0;
    for (long n = card_number; n > 0; n = n / 10) //the length of the number
    {
        checker += 1;
        first_digit = first_digit / 10; //catching the very first numbers to detect VISA or master card
    }    
    int second_digit = (int) first_digit; //no need to keep decimal
    if (checker == 13 || checker == 15 || checker == 16) //checking the length
    {
        for (long n = card_number / 10; n > 0; n = n / 100) //the first step of algorithm
        {
            int m = (n % 10) * 2; //remainder of the division
            if (m > 9)
            {
                int j = m % 10;
                m = m / 10 + j;     
            }
            sum = sum + m ; 
        }    
        for (long n = card_number; n > 0; n = n / 100)//the second step of algorithm
        {  
            sum2 = sum2 + (n % 10) ; //remainder of the division    
        }  
        if ((sum + sum2) % 10 == 0) //final checksum
        {
            bool x = 0; //return invalid 
            if (checker == 15 && (second_digit == 34 || second_digit == 37)) 
            {
                printf("AMEX\n"); 
                x = 1;
            }
            if (checker == 13)
            { 
                printf("VISA\n");
                x = 1;
            }
            if (checker == 16 && (second_digit / 10) == 4) 
            {
                printf("VISA\n");
                x = 1;
            }
            if (checker == 16 && (second_digit == 51 || second_digit == 52 || second_digit == 53 || second_digit == 54 || second_digit == 55))           
            {
                printf("MASTERCARD\n");
                x = 1;
            }
            if (x == 0)
            {
                printf("INVALID\n");
            }
        }   
        else     
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

