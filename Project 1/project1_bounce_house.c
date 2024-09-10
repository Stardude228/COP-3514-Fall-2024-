/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: A local party equipment company */
    /* offers bounce house rentals. The program */
    /* calculates the cost for a bounce house rental. */
/*************************************/

#include <stdio.h>

int main()
{
    int user_choice;
    int days;
    int hours;
    int charge = 10;

    printf("Please select from four bounce houses: 1, 2, 3, and 4 \n");

    printf("Enter bounce house selection: ");
    scanf("%d", &user_choice);

    if(user_choice == 1){

        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        if(hours <= 25 && hours >= 0){
            if(days > 0){
                charge = (days * 80) + (hours * 8);
                printf("Charge($): %d", charge);
            }
            else{
                if(hours <= 3){
                    charge = 58;
                    printf("Charge($): %d", charge);
                }
                else if (hours > 3 && (hours * 8) < 80){
                    charge = (hours * 8);
                    printf("Charge($): %d", charge);
                }
                else{
                    charge = 80;
                    printf("Charge($): %d", charge);
                }
            }
        }
        else
            printf("Invalid hours. \n");
    }

    else if(user_choice == 2){
        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        if(hours <= 25 && hours >= 0){
            if(days > 0){
                charge = (days * 120) + (hours * 12);
                printf("Charge($): %d", charge);
            }
            else{
                if(hours <= 3){
                    charge = 85;
                    printf("Charge($): %d", charge);
                }
                else if (hours > 3 && (hours * 12) < 120){
                    charge = (hours * 12);
                    printf("Charge($): %d", charge);
                }
                else{
                    charge = 120;
                    printf("Charge($): %d", charge);
                }
            }
        }
        else
            printf("Invalid hours. \n");
    }
    else if(user_choice == 3){
        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        if(hours <= 25 && hours >= 0){
            if(days > 0){
                charge = (days * 150) + (hours * 15);
                printf("Charge($): %d", charge);
            }
            else{
                if(hours <= 3){
                    charge = 100;
                    printf("Charge($): %d", charge);
                }
                else if (hours > 3 && (hours * 15) < 150){
                    charge = (hours * 15);
                    printf("Charge($): %d", charge);
                }
                else{
                    charge = 150;
                    printf("Charge($): %d", charge);
                }
            }
        }
        else
            printf("Invalid hours. \n");
    }
    else if(user_choice == 4){

        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        if(hours <= 25 && hours >= 0){
            if(days > 0){
                charge = (days * 250) + (hours * 20);
                printf("Charge($): %d", charge);
            }
            else{
                if(hours <= 3){
                    charge = 180;
                    printf("Charge($): %d", charge);
                }
                else if (hours > 3 && (hours * 20) < 250){
                    charge = (hours * 20);
                    printf("Charge($): %d", charge);
                }
                else{
                    charge = 250;
                    printf("Charge($): %d", charge);
                }
            }
        }
        else
            printf("Invalid hours. \n");
    }
    else
        printf("Invalid selection. Select from 1 to 4.");
}