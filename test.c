#include <stdio.h>
int main(void)
{
    return 0;
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






// STRUCTURES

// #include <stdio.h>
// #define MAX_COLOR 255

// struct color
// {
//     int red;
//     int green;
//     int blue;
// };

// struct color make_color(int red, int green, int blue) {
//     struct color new_color;
    
//     if (red < 0) red = 0;
//     if (red > 255) red = 255;
//     new_color.red = red;
    
//     if (green < 0) green = 0;
//     if (green > 255) green = 255;
//     new_color.green = green;

//     if (blue < 0) blue = 0;
//     if (blue > 255) blue = 255;
//     new_color.blue = blue;

//     return new_color;
// };

// struct color brighter(struct color c) {
//     if (c.red == 0) c.red = 3;
//     if (c.green == 0) c.green = 3;
//     if (c.blue == 0) c.blue = 3;

//     c.red = c.red / 0.7;
//     c.green = c.green / 0.7;
//     c.blue = c.blue / 0.7;

//     if (c.red > 255) c.red = 255;
//     if (c.green > 255) c.green = 255;
//     if (c.blue > 255) c.blue = 255;
    
//     return c;
// };

// int main(void)
// {
//     struct color magenta = {255, 0, 255};
//     printf("Red: %d\n", magenta.red);
//     printf("Green: %d\n", magenta.green);
//     printf("Blue: %d\n", magenta.blue);

//     struct color color2;
//     printf("Color 2 red: ");
//     scanf("%d", &color2.red);
//     printf("Color 2 green: ");
//     scanf("%d", &color2.green);
//     printf("Color 2 blue: ");
//     scanf("%d", &color2.blue);

//     printf("Color 2 red: %d\n", color2.red);
//     printf("Color 2 green: %d\n", color2.green);
//     printf("Color 2 blue: %d\n", color2.blue);

//     struct color gold = make_color (255, 215, 0);
//     struct color brighter_gold = brighter (gold);

//     printf("Gold red: %d\n", gold.red);
//     printf("Gold green: %d\n", gold.green);
//     printf("Gold blue: %d\n", gold.blue);

//     printf("Brighter_gold red: %d\n", brighter_gold.red);
//     printf("Brighter_gold green: %d\n", brighter_gold.green);
//     printf("Brighter_gold blue: %d\n", brighter_gold.blue);

//     return 0;
// }