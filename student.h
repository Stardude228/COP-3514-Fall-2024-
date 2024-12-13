/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: This header file defines data structures */
    /* and declares functions for student management operations. */
/*************************************/
#ifndef STUDENT_H
#define STUDENT_H

#define NAME_LEN 100
#define NETID_LEN 40

struct student {
	char name[NAME_LEN+1], netid[NETID_LEN+1], cop2510_grade;
	double gpa;
	int attempts;
	struct student *next;
};

// function prototypes 

void help();
void read(char *name, char *netid, char *cop2510_grade, double *gpa, int *attempts);
struct student * add_student(struct student *registration, char *name, char *netid, char cop2510_grade, double gpa, int attempts);
struct student * pop_student(struct student *registration);
void list_students(struct student *registration);
void list_gpa_min(struct student *registration, double gpa);
void list_cop2510_min(struct student *registration, int cop2510_grade);
struct student * clear_queue(struct student *registration);
#endif