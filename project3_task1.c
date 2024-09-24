/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: The program to */
/* determine if a sequence is a good sequence. */
/* The program displays yes if it is a */
/* good sequence, otherwise it displays no. */
/*************************************/

#include <stdio.h>

/* check if elements is a sqare of any integer less than sequence_size */
int square_num(int array_number, int n)
{
    for (int i = 0; i < n && i * i <= array_number; i++)
    {
        /* the square numbers are being skipped */
        if (i * i == array_number)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    /* General variables for future calculations */
    int output = 0;
    int sequence_size;

    /* Gathering user data from user */
    printf("Enter the size of sequence: ");
    scanf("%d", &sequence_size);

    /* Variable to store the array of numbers */
    int numbers[sequence_size];

    /* Gathering the array of numbers from user */
    printf("Enter numbers: ");
    for (int i = 0; i < sequence_size; i++)
    {
        scanf("%d", &numbers[i]);
    }

    /* For loop that iterates each item to sort them */
    for (int i = 0; i < sequence_size; i++)
    {

        /* Skipping the ones that are smaller */
        if (numbers[i] < sequence_size)
        {
            continue;
        }

        /* Instantly locating the same number as the sequence size */
        else if (numbers[i] == sequence_size)
            output++;

        /* All other cases are sorted through square_num inspection */
        else
        {

            /* square_num inspection */
            if (square_num(numbers[i], sequence_size))
            {
                continue;
            }

            /* If the numbers did not pass the inspection */
            else
                output++;
        }
    }

    /* Printing the answer */
    if (!output)
        printf("Output: yes");
    else
        printf("Output: no");
}
