/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: The program reads in the */
/* size of the sequence and the numbers in the sequence. */
/* The output of the program is the distinct numbers displayed in ascending order. */
/*************************************/

#include <stdio.h>

// Functions sort_array and unique_elements that will sort the array and identify distinct elements, respectively
void sort_array(int sequence[], int length);
int unique_elements(int input[], int length, int output[]);

// The main function
int main() {
    // Declaring the array_size variable, which will hold the size of the array entered by the user
    int array_size;
    printf("Enter the length of the sequence: ");
    // Reading the size of the array from the user
    scanf("%d", &array_size);

    // Arrays input_sequence and distinct_result, which will be passed as arguments when calling the unique_elements function
    int input_sequence[array_size];
    int distinct_result[array_size];
    printf("Enter the sequence: ");
    // Taking elements of the array as input from the user
    for(int i = 0; i < array_size; i++) {
        scanf("%d", &input_sequence[i]);
    }

    // Calling unique_elements, which takes the input_sequence array, its size, and distinct_result as arguments
    // The function returns distinct_count, the number of unique elements found
    int distinct_count = unique_elements(input_sequence, array_size, distinct_result);
    
    // Sorting the distinct_result array using the sort_array function
    sort_array(distinct_result, distinct_count);
    
    // Printing the sorted unique elements
    printf("Distinct sorted output: ");
    for(int i = 0; i < distinct_count; i++) {
        printf("%d ", distinct_result[i]);
    }

    return 0;
}

// Function to find unique elements in an array
int unique_elements(int input[], int length, int output[]) {
    // Initializing unique_count to 1, as the first element is always unique
    int unique_count = 1;
    // The first element of the input array is added to the output array as a unique element
    output[0] = input[0];

    // Looping through the rest of the array elements
    for(int i = 1; i < length; i++) {
        
        int j = 0;
        // Inner loop to compare the current element with all previous elements
        for(j = 0; j < i; j++) {
            // If a match is found, exit the inner loop as the element is not unique
            if(input[i] == input[j]) {
                break;
            }
        }
        // If no match is found, the element is unique and added to the output array
        if(i == j) {
            output[unique_count] = input[i]; 
            unique_count++;
        }
    }
    // Returning the number of unique elements
    return unique_count;
}

// Function to sort the array using selection sort
void sort_array(int sequence[], int length) {

    int i, j, min_position, temp;
    // Loop through the array to find the smallest element in the unsorted section
    for (i = 0; i < length - 1; i++) {
        // Assume the current element is the minimum
        min_position = i;
        // Find the actual minimum element in the remaining unsorted array
        for (j = i + 1; j < length; j++) {
            if (sequence[j] < sequence[min_position]) {
                min_position = j;
            }
        }
        // Swap the found minimum element with the first element of the unsorted section
        temp = sequence[min_position];
        sequence[min_position] = sequence[i];
        sequence[i] = temp;
    }
}
