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
    /* General variables for future calculations */
    int user_choice;
    int days;
    int hours;
    int charge = 10;

    /* Gathering user data from user */
    printf("Please select from four bounce houses: 1, 2, 3, and 4 \n");
    printf("Enter bounce house selection: ");
    scanf("%d", &user_choice);

    /* First case scenario */
    if(user_choice == 1){

        /* Gathering data about rental days and hours */
        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        /* Checking if the amount of hours is right */
        if(hours <= 25 && hours >= 0){

            /* Checking whether the amount of days is less than 0 */
            if(days > 0){

                /* Checking whether the amount maoney exceed the daily max */
                if ((hours * 8) > 80){
                    charge = (days * 80) + 80;
                    printf("Charge($): %d", charge);
                }

                /* If the daily max is not exceeded the calculations are regular */
                else {
                    charge = (days * 80) + (hours * 8);
                    printf("Charge($): %d", charge);
                }
            }
            
            /* If the number of days is less than 0 and the number of hours is less than minimum */
            /* User will be charged the only the first 3-hour (minimum)	*/
            else{
                if(hours <= 3){
                    charge = 58;
                    printf("Charge($): %d", charge);
                }

                /* Checking if the cost for the hours do not exceed the daily max */
                else if (hours > 3 && (hours * 8) < 80){
                    charge = (hours * 8);
                    printf("Charge($): %d", charge);
                }

                /* If the cost for the hours do exceed the daily max */
                /* User will be charged the daily max */
                else{
                    charge = 80;
                    printf("Charge($): %d", charge);
                }
            }
        }
        else
            printf("Invalid hours. \n");
    }

    /* Second case scenario */
    else if(user_choice == 2){

        /* Gathering data about rental days and hours */
        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        /* Checking if the amount of hours is right */
        if(hours <= 25 && hours >= 0){

            /* Checking whether the amount of days is less than 0 */
            if(days > 0){

                /* Checking whether the amount maoney exceed the daily max */
                if ((hours * 12) > 120){
                    charge = (days * 120) + 120;
                    printf("Charge($): %d", charge);
                }

                /* If the daily max is not exceeded the calculations are regular */
                else {
                    charge = (days * 120) + (hours * 12);
                    printf("Charge($): %d", charge);
                }
            }
            /* If the number of days is less than 0 and the number of hours is less than minimum */
            /* User will be charged the only the first 3-hour (minimum)	*/
            else{
                if(hours <= 3){
                    charge = 85;
                    printf("Charge($): %d", charge);
                }

                /* Checking if the cost for the hours do not exceed the daily max */
                else if (hours > 3 && (hours * 12) < 120){
                    charge = (hours * 12);
                    printf("Charge($): %d", charge);
                }

                /* If the cost for the hours do exceed the daily max */
                /* User will be charged the daily max */
                else{
                    charge = 120;
                    printf("Charge($): %d", charge);
                }
            }
        }
        else
            printf("Invalid hours. \n");
    }

    /* Third case scenario */
    else if(user_choice == 3){

        /* Gathering data about rental days and hours */
        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        /* Checking if the amount of hours is right */
        if(hours <= 25 && hours >= 0){

            /* Checking whether the amount of days is less than 0 */
            if(days > 0){

                /* Checking whether the amount maoney exceed the daily max */
                if ((hours * 15) > 150){
                    charge = (days * 150) + 150;
                    printf("Charge($): %d", charge);
                }

                /* If the daily max is not exceeded the calculations are regular */
                else {
                    charge = (days * 150) + (hours * 15);
                    printf("Charge($): %d", charge);
                }
            }

            /* If the number of days is less than 0 and the number of hours is less than minimum */
            /* User will be charged the only the first 3-hour (minimum)	*/
            else{
                if(hours <= 3){
                    charge = 100;
                    printf("Charge($): %d", charge);
                }

                /* Checking if the cost for the hours do not exceed the daily max */
                else if (hours > 3 && (hours * 15) < 150){
                    charge = (hours * 15);
                    printf("Charge($): %d", charge);
                }

                /* If the cost for the hours do exceed the daily max */
                /* User will be charged the daily max */
                else{
                    charge = 150;
                    printf("Charge($): %d", charge);
                }
            }
        }
        else
            printf("Invalid hours. \n");
    }

    /* Fourth case scenario */
    else if(user_choice == 4){

        /* Gathering data */
        printf("Enter days: ");
        scanf("%d", &days);
        printf("Enter hours: ");
        scanf("%d", &hours);

        /* Checking if the amount of hours is right */
        if(hours <= 25 && hours >= 0){

            /* Checking whether the amount of days is less than 0 */
            if(days > 0){

                /* Checking whether the amount maoney exceed the daily max */
                if ((hours * 20) > 250){
                    charge = (days * 250) + 250;
                    printf("Charge($): %d", charge);
                }
                
                /* If the daily max is not exceeded the calculations are regular */
                else {
                    charge = (days * 250) + (hours * 20);
                    printf("Charge($): %d", charge);
                }
            }

            /* If the number of days is less than 0 and the number of hours is less than minimum */
            /* User will be charged the only the first 3-hour (minimum)	*/
            else{
                if(hours <= 3){
                    charge = 180;
                    printf("Charge($): %d", charge);
                }

                /* Checking if the cost for the hours do not exceed the daily max */
                else if (hours > 3 && (hours * 20) < 250){
                    charge = (hours * 20);
                    printf("Charge($): %d", charge);
                }

                /* If the cost for the hours do exceed the daily max */
                /* User will be charged the daily max */
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