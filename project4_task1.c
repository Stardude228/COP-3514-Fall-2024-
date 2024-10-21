/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: Marjorie and John are playing a board game.  */
/* The board consists of N different numbers organized in one row. */
/* The players take turns, and a turn of the game consists of either */
/* picking the first or the last number in the row. The winner is */
/* the player with the highest sum for the picked numbers. */
/*************************************/

#include <stdio.h>

// Global variable to track whose turn it is (1 for Marjorie, 0 for John)
int marjorie_starts_next = 1; 

// Function prototypes
void round_result(int *board, int n);
void update_turn();

int main() {
    int rounds;
    
    // Read the number of rounds
    scanf("%d", &rounds);
    
    // Play each round
    while (rounds-- > 0) {
        int size;
        
        // Read the size of the array for this round
        scanf("%d", &size);
        
        int board[size];
        
        // Use pointer arithmetic to read the elements into the board array
        for (int *ptr = board; ptr < board + size; ptr++) {
            scanf("%d", ptr);
        }
        
        // Call the function to process and print the result of the current round
        round_result(board, size);
        
        // Toggle the first player for the next round
        update_turn();
    }
    
    return 0;
}

// Process a single round and print the result
void round_result(int *board, int n) {
    int *left = board, *right = board + n - 1;
    int marjorie_score = 0, john_score = 0;
    
    // Track whose turn it is in the current round
    int current_turn = marjorie_starts_next;  

    while (left <= right) {
        int selected_value;
        
        // Compare values at the left and right pointers
        if (*left > *right) {
            selected_value = *left;
            left++;
        } else {
            selected_value = *right;
            right--;
        }

        // Add to the respective player's score based on whose turn it is
        if (current_turn) {
            marjorie_score += selected_value;
        } else {
            john_score += selected_value;
        }

        // Toggle the turn
        current_turn = !current_turn;
    }

    // Print the result for the round
    if (marjorie_score > john_score) {
        printf("Marjorie\n");
    } else if (john_score > marjorie_score) {
        printf("John\n");
    } else {
        printf("Draw\n");
    }
}

// Toggle the starting player for the next round
void update_turn() {
    marjorie_starts_next = !marjorie_starts_next;
}