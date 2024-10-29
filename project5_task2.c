/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: Modify your program for project 2, */
/* task #2 with the following changes: The inputs are entered */
/* as command-line arguments. The inputs are single words instead of a sequence of words */
/*************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check if the number of arguments is exactly 3
    if (argc != 3)
    {
        printf("invalid number of arguments");
        return 1;
    }

    int marjorie_score = 0, john_score = 0;
    char *marjorie_word = argv[1];
    char *john_word = argv[2];
    
    // Calculate score for Marjorie's word
    while (*marjorie_word != '\0')
    {
        marjorie_score += (*marjorie_word == 'a' || *marjorie_word == 'e' || *marjorie_word == 'i' || 
                           *marjorie_word == 'o' || *marjorie_word == 'u') ? 1 :
                          (*marjorie_word == 't' || *marjorie_word == 'n' || *marjorie_word == 's' || 
                           *marjorie_word == 'r' || *marjorie_word == 'h') ? 2 : 3;
        marjorie_word++;
    }

    // Calculate score for John's word
    while (*john_word != '\0')
    {
        john_score += (*john_word == 'a' || *john_word == 'e' || *john_word == 'i' || 
                       *john_word == 'o' || *john_word == 'u') ? 1 :
                      (*john_word == 't' || *john_word == 'n' || *john_word == 's' || 
                       *john_word == 'r' || *john_word == 'h') ? 2 : 3;
        john_word++;
    }

    // Compare scores and determine the winner
    if (marjorie_score > john_score)
    {
        printf("Marjorie wins!\n");
    }
    else if (john_score > marjorie_score)
    {
        printf("John wins!\n");
    }
    else
    {
        printf("Play again!\n");
    }

    return 0;
}
