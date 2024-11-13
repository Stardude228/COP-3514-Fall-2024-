#include <stdio.h>
int main(void)
{

}











// LOWER CASE FUNCTION
// printf("Enter the letter that should be lower cased: ");
// char character;
// scanf("%c", &character);
// if(character >= 'A' && character <= 'Z'){
//     character = character - 'A' + 'a';
//     printf("%c", character);
// } else printf("%c", character);

// COMPARISON BETWEEN TWO ARRAYS
// // Variables for array sizes
// int arr_size1;
// int arr_size2;

// // Gathering information for array A
// printf("Input the size of array A: ");
// scanf("%d", &arr_size1);
// int numbers_a[arr_size1];
// printf("Input the numbers for array A: ");
// for(int i = 0; i < arr_size1; i++) {
//     scanf("%d", &numbers_a[i]);
// }

// // Gathering information for array B
// printf("Input the size of array B: ");
// scanf("%d", &arr_size2);
// int numbers_b[arr_size2];
// printf("Input the numbers for array B: ");
// for(int i = 0; i < arr_size2; i++) {
//     scanf("%d", &numbers_b[i]);
// }

// // Displaying array A
// for(int i = 0; i < arr_size1; i++) {
//     printf("%d ", numbers_a[i]);
// }
// printf(" - Array A \n");

// // Displaying array B
// for(int i = 0; i < arr_size2; i++) {
//     printf("%d ", numbers_b[i]);
// }
// printf(" - Array B \n");

// // Info about array C
// int arr_size3 = 0;
// int numbers_c[arr_size3];

// // For loop to go through the arrays
// for(int i = 0; i < arr_size1; i++) {
//     for(int j = 0; j < arr_size2; j++) {
//         if(numbers_a[i] == numbers_b[j]) {
//             numbers_c[i] = numbers_a[i];
//             arr_size3++;
//         }
//     }
// }

// // Displaying array C
// for(int i = 0; i < arr_size3; i++) {
//     printf("%d ", numbers_c[i]);
// }
// printf(" - Array C");

// REVERSE OF THE ARRAY
// int arr_size;

// printf("Input the size of a sequence: ");
// scanf("%d", &arr_size);

// int numbers[arr_size];

// printf("Input the numbers: ");
// for(int i = 0; i < arr_size; i++) {
//     scanf("%d", &numbers[i]);
// }

// for(int i = 0; i < arr_size; i++) {
//     printf("%d ", numbers[i]);
// }

// printf("\n");

// int start = 0;
// int end = arr_size - 1;
// int temp;

// for(int i = 0; i < arr_size/2; i++) {

//     temp = numbers[start];
//     numbers[start] = numbers[end];
//     numbers[end] = temp;

//     start++;
//     end--;
// }

// for(int i = 0; i < arr_size; i++) {
//     printf("%d ", numbers[i]);
// }

// LARGEST AND SECOND LARGEST FUNCTION
// int size;
// int max;
// int s_max;

// printf("Print the size of a sequence: ");
// scanf("%d", &size);

// int numbers[size];

// printf("Print the numbers: ");
// for(int i = 0; i < size; i++) {
//     scanf("%d", &numbers[i]);
// }

// if (numbers[0] > numbers[1]) {
//     max = numbers[0];
//     s_max = numbers[1];
// } else {
//     max = numbers[1];
//     s_max = numbers[0];
// }

// for (int i = 2; i < size; i++) {
//     if (numbers[i] > max) {
//         s_max = max;
//         max = numbers[i];
//     } else if (numbers[i] > s_max) {
//         s_max = numbers[i];
//     }
// }

// printf("The largest: %d \n", max);
// printf("The second largest: %d \n", s_max);