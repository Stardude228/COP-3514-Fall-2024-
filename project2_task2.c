/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: Marjorie really likes playing Scrabble. */
    /* The program below reads these sequences and says who won the game. */
/*************************************/

#include <stdio.h>

int main()
{
    /* General variables for future calculations */
    char marjorie;
    char john;

    int marjorie_score = 0;
    int john_score = 0;

    printf("Enter the first sequence: ");
    while((marjorie = getchar()) != '\n') {
        if (marjorie != ' ') {
                // Check if character is a vowel
                if (marjorie == 'a' || marjorie == 'e' || marjorie == 'i' || marjorie == 'o' || marjorie == 'u') {
                    marjorie_score += 1;
                }
                // Check if character is a popular consonant
                if (marjorie == 't' || marjorie == 'n' || marjorie == 's' || marjorie == 'r' || marjorie == 'h') {
                    marjorie_score += 2;
                }
                // If it's any other letter, it gets 3 points
                marjorie_score += 3;
        }
    }

    printf("Enter the second sequence: ");
    while((john = getchar()) != '\n') {
        if (john != ' ') {
                // Check if character is a vowel
                if (john == 'a' || john == 'e' || john == 'i' || john == 'o' || john == 'u') {
                    john_score += 1;
                }
                // Check if character is a popular consonant
                if (john == 't' || john == 'n' || john == 's' || john == 'r' || john == 'h') {
                    john_score += 2;
                }
                // If it's any other letter, it gets 3 points
                john_score += 3;
        }
    }

    printf("%d\n", marjorie_score);
    printf("%d\n", john_score);

    // Determine the winner
    if (marjorie_score > john_score) {
        printf("Marjorie wins!\n");
    } else if (john_score > marjorie_score) {
        printf("John wins!\n");
    } else {
        printf("Play again!\n");
    }
}