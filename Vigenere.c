#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])
{
    //printf ("argc = %i\n", argc);  
    if (argc != 2) // checking that it's only ./vigenere and one other parameter
    { 
        return 1; // printf("Error, more than one parameter!\n");         
    }
    int n = strlen(argv[1]); 
    char The_modul [n]; //because of /0 symbol
    strcpy(The_modul, argv[1]); //copy one string to another to have a possibility to use array to compare symbols
    for (int i = 0;  i < n; i++)
    {
        //printf ("The_modul = %c ", The_modul[i]);  
        if (isalpha(The_modul[i]) == 0) 
        {
            //printf("It's a trap!\n");
            return 1;              
        }
    }   
    
    int key [n]; // we need to make all of the letters to digits, so we need an array
    for (int i = 0; i < n; i++)
    {
        key[i] = shift(argv[1][i]);//this is our key from command line
    }    
    string plaintext = get_string("Plaintext: ");  // text to cipher
    char plaintext_char[strlen(plaintext)];
    strcpy(plaintext_char, plaintext);  //copy Plaintext string to char to have a possibility to use array to compare symbols
    printf("ciphertext: ");   
    int j = 0;
    int m = strlen(plaintext);
    for (int i = 0; i < m; i++)
    {
       
        if (plaintext_char[i] > 96 && plaintext_char[i] < 123) //check for lowercase letters
        {
            if (plaintext_char[i] + key[j] > 122)
            {
                // printf("The symbol order is %i\n ", plaintext_char[i] + modul - 26);
                printf("%c", plaintext_char[i] + key[j] - 26);                      
            }
            else 
            {
                // printf("The symbol order is %i\n ", plaintext_char[i] + modul);
                printf("%c", plaintext_char[i] + key[j]);      
            }
        }
        else
        {
            if (plaintext_char[i] > 64 && plaintext_char[i] < 91) //check for upcase letters
            {
                if (plaintext_char[i] + key[j] > 90)
                {
                    //    printf("The symbol order is %i\n ", plaintext_char[i] + modul - 26);
                    printf("%c", plaintext_char[i] + key[j] - 26);                 
                }
                else 
                {
                    //    printf("The symbol order is %i\n ", plaintext_char[i] + modul);
                    printf("%c", plaintext_char[i] + key[j]);   
                }
            }
            else 
            {
                printf("%c", plaintext_char[i]);    //if it's not an alphabetic character, we don't need to modificate it
                j--; // because we don't want to check this
            }
        }  
        if (j == (n - 1))
        {
            j = 0;
        }
        else 
        {
            j++;
        }
    }
   
    
    printf("\n ");   
    return 0;    
}

int shift(char c) //the function return suitable digit to each letter
{
    if (islower(c) != 0) // check for lowercase
    {
        int n = c;
        return n - 97;
    }
    else
    {
        int n = c;
        return n - 65;
    }
    return -1;
}
