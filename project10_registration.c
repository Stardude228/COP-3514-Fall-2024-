/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: This program builds upon Project 9 with  */
    /* a key enhancement — dividing the implementation into multiple  */
    /* files. Specifically, the program is now organized into a header file */
    /* named student.h and a corresponding source file, student.c. */
/*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

int main() {
    char operationCode;
    char studentName[NAME_BUFFER_SIZE + 1], universityID[ID_BUFFER_SIZE + 1], gradeAchieved;
    double cumulativeGPA;
    int retryAttempts;

    struct StudentData *recordList = NULL;

    showUsageGuide();
    printf("\n");

    while (1) {
        // Read operation code
		printf("Enter operation code: ");
        scanf(" %c", &operationCode);
        while (getchar() != '\n'); /* skip to end of line */
        // Execute operation
        switch (operationCode) {
            case 'h':
                showUsageGuide();
                break;
            case 'a':
                inputStudentInfo(studentName, universityID, &gradeAchieved, &cumulativeGPA, &retryAttempts);
                recordList = registerStudent(recordList, studentName, universityID, gradeAchieved, cumulativeGPA, retryAttempts);
                break;
            case 'r':
                recordList = deleteStudent(recordList);
                break;
            case 'd':
                printStudentList(recordList);
                break;
            case 'g':
                inputStudentInfo(NULL, NULL, NULL, &cumulativeGPA, NULL);
                filterByGPA(recordList, cumulativeGPA);
                break;
            case 'f':
                inputStudentInfo(NULL, NULL, &gradeAchieved, NULL, NULL);
                filterByGrade(recordList, gradeAchieved);
                break;
            case 'q':
                recordList = resetList(recordList);
                return 0;
            default:
                printf("Invalid operation code!\n");
        }
        printf("\n");
    }
}
