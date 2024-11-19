/*************************************/
/* Name: Oomat Latipov */
/* NetID: U13921223 */
/* Program Description: A studio program reads in data */
/* from a file, finds out who have taken more than a certain */
/* number of lessons, and writes the result to the output file. */
/*************************************/

#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 200
#define MAX_STRING_LEN 100

struct Customer
{
    char email[MAX_STRING_LEN];
    int lessons;
    char name[MAX_STRING_LEN];
};

int filter(struct Customer data[], int total, int lessonLimit, struct Customer output[]);

int main()
{
    struct Customer data[MAX_RECORDS];
    struct Customer output[MAX_RECORDS];
    FILE *inFile, *outFile;
    int total = 0, lessonLimit, matches;

    inFile = fopen("customers.csv", "r");
    if (inFile == NULL)
    {
        printf("Error opening input file\n");
        return 1;
    }

    while (total < MAX_RECORDS &&
            fscanf(inFile, "%[^,],%d,%[^\n]\n", data[total].email, &data[total].lessons, data[total].name) == 3)
    {
        total++;
    }
    fclose(inFile);

    printf("Enter number of lessons: ");
    scanf("%d", &lessonLimit);

    matches = filter(data, total, lessonLimit, output);

    outFile = fopen("result.csv", "w");
    if (outFile == NULL)
    {
        printf("Error opening output file\n");
        return 1;
    }

    for (int i = 0; i < matches; i++)
    {
        fprintf(outFile, "%s, %d, %s\n", output[i].email, output[i].lessons, output[i].name);
    }
    fclose(outFile);

    printf("Output file name: result.csv\n");
    return 0;
}

int filter(struct Customer data[], int total, int lessonLimit, struct Customer output[])
{
    int count = 0;
    for (int i = 0; i < total; i++)
    {
        if (data[i].lessons > lessonLimit)
        {
            output[count++] = data[i];
        }
    }
    return count;
}
