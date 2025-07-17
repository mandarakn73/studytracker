#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void addEntry();
void viewEntries();

int main() {
    int choice;

    while (1) {
        printf("\n===== Study Tracker App =====\n");
        printf("1. Add Study Record\n");
        printf("2. View Study Records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                addEntry();
                break;
            case 2:
                viewEntries();
                break;
            case 3:
                printf("Exiting... Happy Studying!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void addEntry() {
    FILE *fp;
    char subject[MAX], date[MAX];
    float hours;

    fp = fopen("study_log.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Subject: ");
    fgets(subject, MAX, stdin);
    subject[strcspn(subject, "\n")] = 0; // remove newline

    printf("Enter Date (DD-MM-YYYY): ");
    fgets(date, MAX, stdin);
    date[strcspn(date, "\n")] = 0;

    printf("Enter Hours Studied: ");
    scanf("%f", &hours);
    getchar(); // consume newline

    fprintf(fp, "%s,%s,%.2f\n", subject, date, hours);
    fclose(fp);

    printf("Study record added successfully!\n");
}

void viewEntries() {
    FILE *fp;
    char subject[MAX], date[MAX];
    float hours;

    fp = fopen("study_log.txt", "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Study Records ---\n");
    while (fscanf(fp, "%[^,],%[^,],%f\n", subject, date, &hours) != EOF) {
        printf("Subject: %s | Date: %s | Hours: %.2f\n", subject, date, hours);
    }

    fclose(fp);
}
