#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float marks;
} Student;

void addStudent(Student **students, int *count) {
    *students = realloc(*students, (*count + 1) * sizeof(Student));
    if (*students == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    printf("Enter ID: ");
    scanf("%d", &((*students)[*count].id));
    printf("Enter Name: ");
    scanf("%s", (*students)[*count].name);
    printf("Enter Age: ");
    scanf("%d", &((*students)[*count].age));
    printf("Enter Marks: ");
    scanf("%f", &((*students)[*count].marks));
    (*count)++;
}

void displayStudents(Student *students, int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("ID: %d\nName: %s\nAge: %d\nMarks: %.2f\n\n",
               students[i].id, students[i].name, students[i].age, students[i].marks);
    }
}

void findTopStudent(Student *students, int count) {
    if (count == 0) {
        printf("No students available.\n");
        return;
    }
    int topIndex = 0;
    for (int i = 1; i < count; i++) {
        if (students[i].marks > students[topIndex].marks) {
            topIndex = i;
        }
    }
    printf("Top Student\nName: %s\nMarks: %.2f\n",
           students[topIndex].name, students[topIndex].marks);
}

void saveToFile(Student *students, int count) {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %.2f\n",
                students[i].id, students[i].name, students[i].age, students[i].marks);
    }
    fclose(fp);
    printf("Data saved to students.txt\n");
}

void loadFromFile(Student **students, int *count) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("No file found!\n");
        return;
    }
    *count = 0;
    *students = NULL;
    Student temp;
    while (fscanf(fp, "%d %s %d %f", &temp.id, temp.name, &temp.age, &temp.marks) == 4) {
        *students = realloc(*students, (*count + 1) * sizeof(Student));
        (*students)[*count] = temp;
        (*count)++;
    }
    fclose(fp);
    printf("Data loaded from students.txt\n");
}

int main() {
    Student *students = NULL;
    int count = 0, choice;

    while (1) {
        printf("\nStudent Record System =====\n");
        printf("1. Add Student\n2. Display Students\n3. Find Highest Marks\n");
        printf("4. Save to File\n5. Load from File\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(&students, &count); break;
            case 2: displayStudents(students, count); break;
            case 3: findTopStudent(students, count); break;
            case 4: saveToFile(students, count); break;
            case 5: loadFromFile(&students, &count); break;
            case 6: free(students); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}