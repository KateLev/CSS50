#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    while (n < 1 || n > 8)
    {
        n = get_int("What is the height? ");
        if (n > 0 && n < 9)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (j <= n - i)
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf("#");
                    }
                }
                printf("\n");
            }
        }
        else 
        {
            printf("The height must be between 1 and 8!\n");
        }
    }
}
