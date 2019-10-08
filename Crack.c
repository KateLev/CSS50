!!not completed

#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2) // checking that it's only ./crack and one other parameter
    { 
        printf("Error, we need hash function here!\n");
        return 1; //          
    }
    int n = strlen(argv[1]); 
    char Hashed_password [n]; 
    strcpy(Hashed_password, argv[1]); //copy one string to another to have a possibility to use array to compare symbols
    
    for (int i = 0;  i < n; i++)
    {        
        if (isalpha(Hashed_password[i]) == 0) 
        {
            printf("It's a trap!\n");
            return 2;  
        }
    }    
    
    char salt [2];  //Salt is the first two symbol of hashed password
    salt[0]=Hashed_password[0];
    salt[1]=Hashed_password[1];
    char suggested_password[5] = {"Lol"}; //because of "Assume that each password is no longer than five (5) characters"
   // suggested_password = {}"Lol";
  string s = crypt(suggested_password, salt);
    printf("Crypted password is %s\n", s);
    printf("Salt is %s\n", salt);
}
