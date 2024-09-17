/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: Stacey wants to find out which */
    /* Program Design students need help. The program calculates */
    /* the number of oscillating performances for that student. */
/*************************************/

#include <stdio.h>

int main()
{
    /* General variables for future calculations */
    int oscillations = 0;
    int number_of_grades;

    /* Gathering user data from user */
    printf("Enter the number of grades: ");
    scanf("%d", &number_of_grades);

    /* Variable to store the array of grades */
    int grades[number_of_grades];
    
    /* Gathering the array of grades from user */
    printf("Enter the grades:");
    for(int i=0; i < number_of_grades; i++){
        scanf("%d", &grades[i]);
    }

    /* Min and max number for oscillations count */
    int min = grades[0];
    int max = grades[0];

    /* For loop to start the oscillations count */
    for(int i=1; i < number_of_grades; i++){
        /* Increasing oscillations number if the number lower than min */
        if (grades[i] < min) {
            min = grades[i];
            oscillations++;
        }
        /* Increasing oscillations number if the number is bigger than max */
        else if (grades[i] > max) {
            max = grades[i];
            oscillations++;
        }
    }
    printf("%d", oscillations);
}