#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_DOGS 100
#define RATE 35
#define NAME_LEN 50

struct Dog{
    char name[NAME_LEN+1];
    char owner_full_name[NAME_LEN+1];
    int num_nights;
};

// Function prototypes
int find_dog(char *dog_name, char *owner_name, struct Dog list[], int nd);
void insert(struct Dog list[], int *nd);
void search(struct Dog list[], int nd);
void calculate_cost(struct Dog list[], int nd);
void print(struct Dog list[], int nd);
int read_line(char *str, int n);

int main() {
    char code;
    struct Dog dog_list[MAX_DOGS];
    int num_dogs = 0;

    for (; ;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n');  // Clear the newline character

        switch (code) {
            case 'i':
                insert(dog_list, &num_dogs);
                break;
            case 's':
                search(dog_list, num_dogs);
                break;
            case 'c':
                calculate_cost(dog_list, num_dogs);
                break;
            case 'p':
                print(dog_list, num_dogs);
                break;
            case 'q':
                return 0;
            default:
                printf("Illegal code\n");
        }
        printf("\n");
    }

    return 0;
}

int find_dog(char *dog_name, char *owner_name, struct Dog list[], int nd) {
    int i;
    for (i = 0; i < nd; i++) {
        if (strcmp(list[i].name, dog_name) == 0 && strcmp(list[i].owner_full_name, owner_name) == 0) {
            return i;
        }
    }
    return -1;
}

void insert(struct Dog list[], int *nd) {
    char dog_name[50], owner_name[50];
    int nights;
    if (*nd == MAX_DOGS) {
        printf("Database is full; can't add more dogs.\n");
        return;
    }

    printf("Enter dog name: ");
    read_line(dog_name, NAME_LEN);
    
    printf("Enter owner full name: ");
    read_line(owner_name, NAME_LEN);
    
    printf("Enter number of nights for boarding: ");
    scanf("%d", &nights);
    
    strcpy(list[*nd].name, dog_name);
    strcpy(list[*nd].owner_full_name, owner_name);
    list[*nd].num_nights = nights;
    (*nd)++;
}

void search(struct Dog list[], int nd) {
    char dog_name[50], owner_name[50];
    printf("Enter dog name: ");
    read_line(dog_name, NAME_LEN);

    printf("Enter owner full name: ");
    read_line(owner_name, NAME_LEN);
    
    int i = find_dog(dog_name, owner_name, list, nd);
    if (i >= 0) {
        printf("Dog found. Staying for %d nights\n", list[i].num_nights);
    } else {
        printf("Dog not found.\n");
    }
}

void calculate_cost(struct Dog list[], int nd) {
    char dog_name[NAME_LEN], owner_name[NAME_LEN];
    printf("Enter dog name: ");
    read_line(dog_name, NAME_LEN);

    printf("Enter owner's full name: ");
    read_line(owner_name, NAME_LEN);

    int i = find_dog(dog_name, owner_name, list, nd);
    if (i >= 0) {
        printf("Dog found. Cost of nights for boarding $%d\n", list[i].num_nights * 20);
    } else {
        printf("Dog not found.\n");
    }
}

void print(struct Dog list[], int nd) {
    int i;
    printf("%-15s %-25s %-8s\n", "Dog Name", "Owner Name", "# of nights");
    for (i = 0; i < nd; i++) {
        printf("%-15s %-25s %-8d\n", list[i].name, list[i].owner_full_name, list[i].num_nights);
    }
}

int read_line(char *str, int n){
    int ch; int i = 0;
    while(isspace(ch = getchar()));
    *str++ = ch;

	while ((ch = getchar()) != '\n'){ 
		if (i < n){
			*str++= ch;
            i++;
        }
	}

    *str = '\0';   /* terminates string */
    return i;        /* number of characters stored */
}
