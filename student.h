/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: This header file defines data structures */
    /* and declares functions for student management operations. */
/*************************************/

#ifndef STUDENT_DATA_H
#define STUDENT_DATA_H

#define NAME_BUFFER_SIZE 100
#define ID_BUFFER_SIZE 40

struct StudentData {
    char studentName[NAME_BUFFER_SIZE + 1], universityID[ID_BUFFER_SIZE + 1], gradeAchieved;
    double cumulativeGPA;
    int retryAttempts;
    struct StudentData *nextEntry;
};

// Function Declarations

void showUsageGuide();
void inputStudentInfo(char *studentName, char *universityID, char *gradeAchieved, double *cumulativeGPA, int *retryAttempts);
struct StudentData * registerStudent(struct StudentData *currentList, char *studentName, char *universityID, char gradeAchieved, double cumulativeGPA, int retryAttempts);
struct StudentData * deleteStudent(struct StudentData *currentList);
void printStudentList(struct StudentData *currentList);
void filterByGPA(struct StudentData *currentList, double gpaThreshold);
void filterByGrade(struct StudentData *currentList, int gradeThreshold);
struct StudentData * resetList(struct StudentData *currentList);

#endif
