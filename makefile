/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: This file contains the   */
    /* instructions for creating a file. */
/*************************************/

project10_registration: project10_registration.o student.o
	gcc -o project10_registration project10_registration.o student.o
project10_registration.o: project10_registration.c student.h
	gcc -c project10_registration.c
student.o: student.c student.h
	gcc -c student.c