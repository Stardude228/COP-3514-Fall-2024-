/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: You are given an array a consisting of */
/* N positive integers. For each position of the array, print */
/* how many times the number in that position was seen before */
/* and after that position. */
/*************************************/

#include <stdio.h>

// Function prototype
void before_after(int *array, int n);

int main() {
    int n;
    scanf("%d", &n);  // Input the size of the array

    int a[1000];
    for (int *ptr = a; ptr < a + n; ptr++) {
        scanf("%d", ptr);  // Input the array elements using pointer arithmetic
    }

    before_after(a, n);  // Call the function to process the array

    return 0;
}

// Function to count occurrences before and after each element
void before_after(int *array, int n) {
    for (int *current = array; current < array + n; current++) {
        int before = 0, after = 0;

        // Count occurrences before the current position
        for (int *ptr = array; ptr < current; ptr++) {
            if (*ptr == *current) {
                before++;
            }
        }

        // Count occurrences after the current position
        for (int *ptr = current + 1; ptr < array + n; ptr++) {
            if (*ptr == *current) {
                after++;
            }
        }

        printf("%d %d\n", before, after);  // Output the result
    }
}