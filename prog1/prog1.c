#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    int score;
} Record;

void write_records(const char *filename, int n) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Unable to open file for writing");
        return;
    }

    for (int i = 0; i < n; i++) {
        Record rec;
        printf("Enter id for record %d: ", i + 1);
        scanf("%d", &rec.id);
        getchar();
        printf("Enter name for record %d: ", i + 1);
        fgets(rec.name, MAX_NAME, stdin);
        rec.name[strcspn(rec.name, "\n")] = '\0';
        printf("Enter score for record %d: ", i + 1);
        scanf("%d", &rec.score);
        getchar();

        fwrite(&rec, sizeof(Record), 1, fp);
    }

    fclose(fp);
}

int get_record(const char *filename, int m, Record *rec) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Unable to open file");
        return 0;
    }

    if (fseek(fp, (m - 1) * sizeof(Record), SEEK_SET) != 0) {
        fclose(fp);
        return 0;
    }

    int read = fread(rec, sizeof(Record), 1, fp);
    fclose(fp);
    return read == 1;
}

int delete_record(const char *filename, int m) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Unable to open file");
        return 0;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (!temp) {
        perror("Unable to open temporary file");
        fclose(fp);
        return 0;
    }

    Record rec;
    int index = 1;
    int deleted = 0;
    while (fread(&rec, sizeof(Record), 1, fp) == 1) {
        if (index == m) {
            deleted = 1;
        } else {
            fwrite(&rec, sizeof(Record), 1, temp);
        }
        index++;
    }

    fclose(fp);
    fclose(temp);

    if (!deleted) {
        remove("temp.bin");
        return 0;
    }

    if (remove(filename) != 0 || rename("temp.bin", filename) != 0) {
        perror("Unable to update file after deletion");
        return 0;
    }

    return 1;
}

void display_record(const Record *rec) {
    printf("Id: %d\n", rec->id);
    printf("Name: %s\n", rec->name);
    printf("Score: %d\n", rec->score);
}

void display_all(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    Record rec;
    int index = 1;
    while (fread(&rec, sizeof(Record), 1, fp) == 1) {
        printf("Record %d:\n", index);
        display_record(&rec);
        printf("\n");
        index++;
    }

    fclose(fp);
}

int main(void) {
    const char *filename = "records.bin";
    int choice;
    int n;

    do {
        printf("\nMenu:\n");
        printf("1. Create records\n");
        printf("2. Get mth record\n");
        printf("3. Delete mth record\n");
        printf("4. Display all records\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("Enter number of records: ");
            scanf("%d", &n);
            getchar();
            write_records(filename, n);
        } else if (choice == 2) {
            int m;
            printf("Enter record number to display: ");
            scanf("%d", &m);
            getchar();
            Record rec;
            if (get_record(filename, m, &rec)) {
                display_record(&rec);
            } else {
                printf("Record %d not found.\n", m);
            }
        } else if (choice == 3) {
            int m;
            printf("Enter record number to delete: ");
            scanf("%d", &m);
            getchar();
            if (delete_record(filename, m)) {
                printf("Deleted record %d.\n", m);
            } else {
                printf("Record %d not found or delete failed.\n", m);
            }
        } else if (choice == 4) {
            display_all(filename);
        }
    } while (choice != 5);

    return 0;
}
