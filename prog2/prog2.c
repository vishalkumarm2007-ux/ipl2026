#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure definition
struct Student {
    int id;
    char name[50];
    float marks;
};

// Function to write array of structures into ASCII file
void writeToFile(struct Student s[], int n, const char *filename) {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %.2f\n",
                s[i].id,
                s[i].name,
                s[i].marks);
    }

    fclose(fp);
}

// Function to create array of seek positions
void createSeekArray(long pos[], int *count, const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int i = 0;

    while (!feof(fp)) {

        // Store beginning position of record
        pos[i] = ftell(fp);

        int id;
        char name[50];
        float marks;

        if (fscanf(fp, "%d %s %f",
                   &id,
                   name,
                   &marks) != 3) {
            break;
        }

        i++;
    }

    *count = i;

    fclose(fp);
}

// Function to display record using seek position
void displayRecordAtPos(long pos, const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Move file pointer to required position
    fseek(fp, pos, SEEK_SET);

    int id;
    char name[50];
    float marks;

    if (fscanf(fp, "%d %s %f",
               &id,
               name,
               &marks) == 3) {

        printf("\nRecord Found:\n");
        printf("ID    : %d\n", id);
        printf("Name  : %s\n", name);
        printf("Marks : %.2f\n", marks);

    } else {
        printf("Invalid position!\n");
    }

    fclose(fp);
}

// Main function
int main() {

    struct Student s[MAX];
    long pos[MAX];

    int n, count;

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Input student details
    for (int i = 0; i < n; i++) {

        printf("\nEnter details for student %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &s[i].id);

        printf("Enter Name: ");
        scanf("%s", s[i].name);

        printf("Enter Marks: ");
        scanf("%f", &s[i].marks);
    }

    // Write structures to file
    writeToFile(s, n, "students.txt");

    // Create seek position array
    createSeekArray(pos, &count, "students.txt");

    // Display stored positions
    printf("\nSeek Positions:\n");

    for (int i = 0; i < count; i++) {
        printf("Record %d starts at byte %ld\n",
               i + 1,
               pos[i]);
    }

    // Select record to display
    int choice;

    printf("\nEnter record number to display: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= count) {
        displayRecordAtPos(pos[choice - 1], "students.txt");
    } else {
        printf("Invalid record number!\n");
    }

    return 0;
}