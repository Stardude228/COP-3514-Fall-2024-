#include <stdio.h>
#define N 26

int main() {

	char character;
	int i, count[N] = 0;
    int count2[N] = 0;
    int count_zeros = 0;

	printf("Enter the first sequence: ");
	while ((character = getchar()) != '\n') {
		count[character-'a']++;
	}

    for (i = 0; i < N; i++) {
        printf("%d", count[i]);
    }

	printf("Enter the first sequence: ");
	while ((character = getchar()) != '\n') {
		count2[character-'a']--;
	}
	
	for (i = 0; i < N; i++) {
        if(count[i] == 0)
            count_zeros++;
    }
    
    if(count_zeros == N)
        printf("The words are anagrams\n");
    else printf("The words are NOT anagrams\n");
}