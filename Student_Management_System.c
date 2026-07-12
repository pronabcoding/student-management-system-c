#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Constants
#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_EMAIL 50
#define MAX_PHONE 15
#define MAX_ADDRESS 100
#define MAX_COURSES 5
#define FILENAME "students.dat"

// Structure for Course
typedef struct {
    char courseName[30];
    char courseCode[10];
    float marks;
    int credits;
} Course;

// Structure for Student
typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    char email[MAX_EMAIL];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
    char department[30];
    int semester;
    float cgpa;
    Course courses[MAX_COURSES];
    int courseCount;
    char enrollmentDate[20];
    int isActive;
} Student;

// Global Variables
Student students[MAX_STUDENTS];
int studentCount = 0;
int nextId =1;

// Function Declarations
void clearScreen();
void pause();
void printLine();
void printTitle(const char* title);
void displayMainMenu();
void displaySearchMenu();
void displaySortMenu();
void displayReportMenu();

// CRUD Operations
void addStudent();
void viewAllStudents();
void viewStudentDetails();
void updateStudent();
void deleteStudent();

// Search Operations
void searchById();
void searchByName();
void searchByDepartment();
void searchByCGPA();

// Sort Operations
void sortById();
void sortByName();
void sortByCGPA();
void sortByDepartment();

// Course Operations
void addCourseToStudent(int index);
void viewStudentCourses(int index);
void updateCourse(int index);
void deleteCourse(int index);
void calculateCGPA(int index);

// Report Operations
void displayStatistics();
void generateDepartmentReport();
void generateCGPAReport();
void generateToppersList();
void generateFailingStudents();
void exportToCSV();

// File Operations
void saveToFile();
void loadFromFile();
void createBackup();
void restoreFromBackup();

// Utility Functions
int isValidEmail(const char* email);
int findStudentById(int id);
void getCurrentDate(char* date);
void trim(char* str);

//  MAIN FUNCTION
int main() {
    int choice;
    
    // Load existing data
    loadFromFile();
    
    while (1) {
        displayMainMenu();
        printf("\n\tEnter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("\n\tInvalid input! Please enter a number.\n");
            pause();
            continue;
        }
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                viewStudentDetails();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                displaySearchMenu();
                break;
            case 7:
                displaySortMenu();
                break;
            case 8:
                displayReportMenu();
                break;
            case 9:
                saveToFile();
                printf("\n\tData saved successfully!\n");
                pause();
                break;
            case 10:
                createBackup();
                break;
            case 11:
                restoreFromBackup();
                break ;
            case 0:
                printf("\n\tSaving data before exit...\n");
                saveToFile();
                printf("\n\tThank you for using Student Management System!\n");
                printf("\n\tGoodbye!\n\n");
                exit(0);
            default:
                printf("\n\tInvalid choice! Please try again.\n");
                pause();
        }
    }
    
    return 0;
}

// DISPLAY  MENU FUNCTIONS
void displayMainMenu() {
    clearScreen();
    printTitle("STUDENT MANAGEMENT SYSTEM");
    
    printf("\n\t=======================================================\n");
    printf("\t                    MAIN MENU\n");
    printf("\t========================================================\n");
    printf("\t  1.  Add New Student\n");
    printf("\t  2.  View All Students\n");
    printf("\t  3.  View Student Details\n");
    printf("\t  4.  Update Student Information\n");
    printf("\t  5.  Delete Student\n");
    printf("\t  6.  Search Students\n");
    printf("\t  7.  Sort Students\n");
    printf("\t  8.  Reports & Statistics\n");
    printf("\t  9.  Save Data\n");
    printf("\t  10. Create Backup\n");
    printf("\t  11. Restore  from Backup\n");
    printf("\t  0.  Exit\n");
    printf("\t========================================================\n");
    printf("\n\t  Total Students: %d\n", studentCount);
}

void displaySearchMenu() {
    int choice;
    clearScreen();
    printTitle("SEARCH STUDENTS");
    
    printf("\n\t========================================================\n");
    printf("\t  1. Search by ID\n");
    printf("\t  2. Search by Name\n");
    printf("\t  3. Search by Department\n");
    printf("\t  4. Search by CGPA Range\n");
    printf("\t  0. Back to Main Menu\n");
    printf("\t========================================================\n");
    
    printf("\n\tEnter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    
    switch (choice) {
        case 1: searchById(); break;
        case 2: searchByName(); break;
        case 3: searchByDepartment(); break;
        case 4: searchByCGPA(); break;
        case 0: return;
        default:
            printf("\n\tInvalid choice!\n");
            pause();
    }
}

void displaySortMenu() {
    int choice;
    clearScreen();
    printTitle("SORT STUDENTS");
    
    printf("\n\t=======================================================\n");
    printf("\t  1. Sort by ID\n");
    printf("\t  2. Sort by Name\n");
    printf("\t  3. Sort by CGPA\n");
    printf("\t  4. Sort by Department\n");
    printf("\t  0. Back to Main Menu\n");
    printf("\t=======================================================\n");
    
    printf("\n\tEnter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    
    switch (choice) {
        case 1: sortById(); break;
        case 2: sortByName(); break;
        case 3: sortByCGPA(); break;
        case 4: sortByDepartment(); break;
        case 0: return;
        default:
            printf("\n\tInvalid choice!\n");
            pause();
    }
}

void displayReportMenu() {
    int choice;
    clearScreen();
    printTitle("REPORTS & STATISTICS");
    
    printf("\n\t========================================================\n");
    printf("\t  1. Display Statistics\n");
    printf("\t  2. Department-wise Report\n");
    printf("\t  3. CGPA Distribution Report\n");
    printf("\t  4. Top 10 Students\n");
    printf("\t  5. Failing Students (CGPA < 2.0)\n");
    printf("\t  6. Export to CSV\n");
    printf("\t  0. Back to Main Menu\n");
    printf("\t========================================================\n");
    
    printf("\n\tEnter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    
    switch (choice) {
        case 1: displayStatistics(); break;
        case 2: generateDepartmentReport(); break;
        case 3: generateCGPAReport(); break;
        case 4: generateToppersList(); break;
        case 5: generateFailingStudents(); break;
        case 6: exportToCSV(); break;
        case 0: return;
        default:
            printf("\n\tInvalid choice!\n");
            pause();
    }
}

//  CRUD OPERATIONS
void addStudent() {
    clearScreen();
    printTitle("ADD NEW STUDENT");
    
    if (studentCount >= MAX_STUDENTS) {
        printf("\n\tDatabase is full! Cannot add more students.\n");
        pause();
        return;
    }
    
    Student newStudent;
    newStudent.id = nextId++;
    newStudent.isActive = 1;
    newStudent.courseCount = 0;
    
    printf("\n\tEnter Student Details:\n");
    printLine();
    
    printf("\n\tName: ");
    fgets(newStudent.name, MAX_NAME, stdin);
    trim(newStudent.name);
    
    printf("\tAge: ");
    scanf("%d", &newStudent.age);
    while (getchar() != '\n');
    
    printf("\tEmail: ");
    fgets(newStudent.email, MAX_EMAIL, stdin);
    trim(newStudent.email);
    
    if (!isValidEmail(newStudent.email)) {
        printf("\n\tWarning: Email format may be invalid.\n");
    }
    
    printf("\tPhone: ");
    fgets(newStudent.phone, MAX_PHONE, stdin);
    trim(newStudent.phone);
    
    printf("\tAddress: ");
    fgets(newStudent.address, MAX_ADDRESS, stdin);
    trim(newStudent.address);
    
    printf("\tDepartment: ");
    fgets(newStudent.department, 30, stdin);
    trim(newStudent.department);
    
    printf("\tSemester: ");
    scanf("%d", &newStudent.semester);
    while (getchar() != '\n');
    
    printf("\tCGPA: ");
    scanf("%f", &newStudent.cgpa);
    while (getchar() != '\n');
    
    getCurrentDate(newStudent.enrollmentDate);
    
    students[studentCount++] = newStudent;
    
    printf("\n\t>>> Student added successfully!\n");
    printf("\tStudent ID: %d\n", newStudent.id);
    
    char choice;
    printf("\n\tDo you want to add courses for this student? (y/n): ");
    scanf(" %c", &choice);
    while (getchar() != '\n');
    
    if (choice == 'y' || choice == 'Y') {
        addCourseToStudent(studentCount - 1);
    }
    
    pause();
}

void viewAllStudents() {
    clearScreen();
    printTitle("ALL STUDENTS");
    
    if (studentCount == 0) {
        printf("\n\tNo students found in the database.\n");
        pause();
        return;
    }
    
    printf("\n\t%-5s %-20s %-15s %-8s %-6s\n", 
           "ID", "Name", "Department", "Semester", "CGPA");
    printLine();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            printf("\t%-5d %-20s %-15s %-8d %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].department,
                   students[i].semester,
                   students[i].cgpa);
        }
    }
    
    printf("\n\tTotal Active Students: %d\n", studentCount);
    pause();
}

void viewStudentDetails() {
    clearScreen();
    printTitle("VIEW STUDENT DETAILS");
    
    int id;
    printf("\n\tEnter Student ID: ");
    scanf("%d", &id);
    while (getchar() != '\n');
    
    int index = findStudentById(id);
    
    if (index == -1) {
        printf("\n\tStudent not found!\n");
        pause();
        return;
    }
    
    Student s = students[index];
    
    printf("\n\t========================================================\n");
    printf("\t              STUDENT INFORMATION\n");
    printf("\t========================================================\n");
    
    printf("\n\tID:             %d\n", s.id);
    printf("\tName:           %s\n", s.name);
    printf("\tAge:            %d\n", s.age);
    printf("\tEmail:          %s\n", s.email);
    printf("\tPhone:          %s\n", s.phone);
    printf("\tAddress:        %s\n", s.address);
    printf("\tDepartment:     %s\n", s.department);
    printf("\tSemester:       %d\n", s.semester);
    printf("\tCGPA:           %.2f\n", s.cgpa);
    printf("\tEnrollment Date: %s\n", s.enrollmentDate);
    
    if (s.courseCount > 0) {
        printf("\n\t========================================================\n");
        printf("\t                   COURSES\n");
        printf("\t========================================================\n");
        
        printf("\n\t%-10s %-20s %-8s %-8s\n",
               "Code", "Name", "Credits", "Marks");
        printLine();
        
        for (int i = 0; i < s.courseCount; i++) {
            printf("\t%-10s %-20s %-8d %.2f\n",
                   s.courses[i].courseCode,
                   s.courses[i].courseName,
                   s.courses[i].credits,
                   s.courses[i].marks);
        }
    }
    
    pause();
}

void updateStudent() {
    clearScreen();
    printTitle("UPDATE STUDENT INFORMATION");
    
    int id;
    printf("\n\tEnter Student ID to update: ");
    scanf("%d", &id);
    while (getchar() != '\n');
    
    int index = findStudentById(id);
    
    if (index == -1) {
        printf("\n\tStudent not found!\n");
        pause();
        return;
    }
    
    int choice;
    printf("\n\tWhat do you want to update?\n");
    printf("\t1. Name\n");
    printf("\t2. Age\n");
    printf("\t3. Email\n");
    printf("\t4. Phone\n");
    printf("\t5. Address\n");
    printf("\t6. Department\n");
    printf("\t7. Semester\n");
    printf("\t8. CGPA\n");
    printf("\t9. Manage Courses\n");
    printf("\n\tChoice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    
    switch (choice) {
        case 1:
            printf("\tNew Name: ");
            fgets(students[index].name, MAX_NAME, stdin);
            trim(students[index].name);
            break;
        case 2:
            printf("\tNew Age: ");
            scanf("%d", &students[index].age);
            while (getchar() != '\n');
            break;
        case 3:
            printf("\tNew Email: ");
            fgets(students[index].email, MAX_EMAIL, stdin);
            trim(students[index].email);
            break;
        case 4:
            printf("\tNew Phone: ");
            fgets(students[index].phone, MAX_PHONE, stdin);
            trim(students[index].phone);
            break;
        case 5:
            printf("\tNew Address: ");
            fgets(students[index].address, MAX_ADDRESS, stdin);
            trim(students[index].address);
            break;
        case 6:
            printf("\tNew Department: ");
            fgets(students[index].department, 30, stdin);
            trim(students[index].department);
            break;
        case 7:
            printf("\tNew Semester: ");
            scanf("%d", &students[index].semester);
            while (getchar() != '\n');
            break;
        case 8:
            printf("\tNew CGPA: ");
            scanf("%f", &students[index].cgpa);
            while (getchar() != '\n');
            break;
        case 9:
            viewStudentCourses(index);
            break;
        default:
            printf("\n\tInvalid choice!\n");
            pause();
            return;
    }
    
    printf("\n\t>>> Student information updated successfully!\n");
    pause();
}

void deleteStudent() {
    clearScreen();
    printTitle("DELETE STUDENT");
    
    int id;
    printf("\n\tEnter Student ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n');
    
    int index = findStudentById(id);
    
    if (index == -1) {
        printf("\n\tStudent not found!\n");
        pause();
        return;
    }
    
    printf("\n\tStudent: %s (ID: %d)\n", students[index].name, students[index].id);
    printf("\n\tAre you sure you want to delete? (y/n): ");
    
    char confirm;
    scanf(" %c", &confirm);
    while (getchar() != '\n');
    
    if (confirm == 'y' || confirm == 'Y') {
        students[index].isActive = 0;
        printf("\n\t>>> Student deleted successfully!\n");
    } else {
        printf("\n\tDeletion cancelled.\n");
    }
    
    pause();
}

//  COURSE OPERATIONS
void addCourseToStudent(int index) {
    if (students[index].courseCount >= MAX_COURSES) {
        printf("\n\tMaximum courses limit reached!\n");
        return;
    }
    
    Course newCourse;
    
    printf("\n\tEnter Course Code: ");
    fgets(newCourse.courseCode, 10, stdin);
    trim(newCourse.courseCode);
    
    printf("\tEnter Course Name: ");
    fgets(newCourse.courseName, 30, stdin);
    trim(newCourse.courseName);
    
    printf("\tEnter Credits: ");
    scanf("%d", &newCourse.credits);
    
    printf("\tEnter Marks: ");
    scanf("%f", &newCourse.marks);
    while (getchar() != '\n');
    
    students[index].courses[students[index].courseCount++] = newCourse;
    calculateCGPA(index);
    
    printf("\n\t>>> Course added successfully!\n");
}

void viewStudentCourses(int index) {
    clearScreen();
    printTitle("MANAGE STUDENT COURSES");
    
    if (students[index].courseCount == 0) {
        printf("\n\tNo courses added yet.\n");
        
        char choice;
        printf("\n\tDo you want to add a course? (y/n): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
        if (choice == 'y' || choice == 'Y') {
            addCourseToStudent(index);
        }
        return;
    }
    
    printf("\n\t%-5s %-10s %-20s %-8s %-8s\n",
           "No.", "Code", "Name", "Credits", "Marks");
    printLine();
    
    for (int i = 0; i < students[index].courseCount; i++) {
        printf("\t%-5d %-10s %-20s %-8d %.2f\n",
               i + 1,
               students[index].courses[i].courseCode,
               students[index].courses[i].courseName,
               students[index].courses[i].credits,
               students[index].courses[i].marks);
    }
    
    printf("\n\tOptions:\n");
    printf("\t1. Add Course\n");
    printf("\t2. Update Course\n");
    printf("\t3. Delete Course\n");
    printf("\t0. Back\n");
    
    int choice;
    printf("\n\tChoice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    
    switch (choice) {
        case 1: addCourseToStudent(index); break;
        case 2: updateCourse(index); break;
        case 3: deleteCourse(index); break;
    }
}

void updateCourse(int index) {
    int courseNum;
    printf("\n\tEnter course number to update: ");
    scanf("%d", &courseNum);
    while (getchar() != '\n');
    
    if (courseNum < 1 || courseNum > students[index].courseCount) {
        printf("\n\tInvalid course number!\n");
        pause();
        return;
    }
    
    courseNum--;
    
    printf("\tNew Marks: ");
    scanf("%f", &students[index].courses[courseNum].marks);
    while (getchar() != '\n');
    
    calculateCGPA(index);
    printf("\n\t>>> Course updated successfully!\n");
    pause();
}

void deleteCourse(int index) {
    int courseNum;
    printf("\n\tEnter course number to delete: ");
    scanf("%d", &courseNum);
    while (getchar() != '\n');
    
    if (courseNum < 1 || courseNum > students[index].courseCount) {
        printf("\n\tInvalid course number!\n");
        pause();
        return;
    }
    
    courseNum--;
    
    for (int i = courseNum; i < students[index].courseCount - 1; i++) {
        students[index].courses[i] = students[index].courses[i + 1];
    }
    
    students[index].courseCount--;
    calculateCGPA(index);
    
    printf("\n\t>>> Course deleted successfully!\n");
    pause();
}

void calculateCGPA(int index) {
    if (students[index].courseCount == 0) {
        students[index].cgpa = 0.0;
        return;
    }
    
    float totalMarks = 0;
    int totalCredits = 0;
    
    for (int i = 0; i < students[index].courseCount; i++) {
        float gradePoint;
        float marks = students[index].courses[i].marks;
        
        if (marks >= 80) gradePoint = 4.0;
        else if (marks >= 75) gradePoint = 3.75;
        else if (marks >= 70) gradePoint = 3.5;
        else if (marks >= 65) gradePoint = 3.25;
        else if (marks >= 60) gradePoint = 3.0;
        else if (marks >= 55) gradePoint = 2.75;
        else if (marks >= 50) gradePoint = 2.5;
        else if (marks >= 45) gradePoint = 2.25;
        else if (marks >= 40) gradePoint = 2.0;
        else gradePoint = 0.0;
        
        totalMarks += gradePoint * students[index].courses[i].credits;
        totalCredits += students[index].courses[i].credits;
    }
    
    students[index].cgpa = totalCredits > 0 ? totalMarks / totalCredits : 0.0;
}

// SEARCH OPERATIONS
void searchById() {
    clearScreen();
    printTitle("SEARCH BY ID");
    
    int id;
    printf("\n\tEnter Student ID: ");
    scanf("%d", &id);
    while (getchar() != '\n');
    
    int index = findStudentById(id);
    
    if (index == -1) {
        printf("\n\tStudent not found!\n");
    } else {
        printf("\n\tStudent Found:\n");
        printf("\n\t%-5s %-20s %-15s %-8s %-6s\n",
               "ID", "Name", "Department", "Semester", "CGPA");
        printLine();
        printf("\t%-5d %-20s %-15s %-8d %.2f\n",
               students[index].id,
               students[index].name,
               students[index].department,
               students[index].semester,
               students[index].cgpa);
    }
    
    pause();
}

void searchByName() {
    clearScreen();
    printTitle("SEARCH BY NAME");
    
    char searchName[MAX_NAME];
    printf("\n\tEnter student name (or part of it): ");
    fgets(searchName, MAX_NAME, stdin);
    trim(searchName);
    
    int found = 0;
    
    printf("\n\t%-5s %-20s %-15s %-8s %-6s\n",
           "ID", "Name", "Department", "Semester", "CGPA");
    printLine();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && strstr(students[i].name, searchName) != NULL) {
            printf("\t%-5d %-20s %-15s %-8d %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].department,
                   students[i].semester,
                   students[i].cgpa);
            found++;
        }
    }
    
    if (found == 0) {
        printf("\n\tNo students found with that name.\n");
    } else {
        printf("\n\tTotal students found: %d\n", found);
    }
    
    pause();
}

void searchByDepartment() {
    clearScreen();
    printTitle("SEARCH BY DEPARTMENT");
    
    char dept[30];
    printf("\n\tEnter department name: ");
    fgets(dept, 30, stdin);
    trim(dept);
    
    int found = 0;
    
    printf("\n\t%-5s %-20s %-15s %-8s %-6s\n",
           "ID", "Name", "Department", "Semester", "CGPA");
    printLine();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && strcasecmp(students[i].department, dept) == 0) {
            printf("\t%-5d %-20s %-15s %-8d %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].department,
                   students[i].semester,
                   students[i].cgpa);
            found++;
        }
    }
    
    if (found == 0) {
        printf("\n\tNo students found in that department.\n");
    } else {
        printf("\n\tTotal students found: %d\n", found);
    }
    
    pause();
}

void searchByCGPA() {
    clearScreen();
    printTitle("SEARCH BY CGPA RANGE");
    
    float minCGPA, maxCGPA;
    printf("\n\tEnter minimum CGPA: ");
    scanf("%f", &minCGPA);
    printf("\tEnter maximum CGPA: ");
    scanf("%f", &maxCGPA);
    while (getchar() != '\n');
    
    int found = 0;
    
    printf("\n\t%-5s %-20s %-15s %-8s %-6s\n",
           "ID", "Name", "Department", "Semester", "CGPA");
    printLine();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && 
            students[i].cgpa >= minCGPA && 
            students[i].cgpa <= maxCGPA) {
            printf("\t%-5d %-20s %-15s %-8d %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].department,
                   students[i].semester,
                   students[i].cgpa);
            found++;
        }
    }
    
    if (found == 0) {
        printf("\n\tNo students found in that CGPA range.\n");
    } else {
        printf("\n\tTotal students found: %d\n", found);
    }
    
    pause();
}

// SORT OPERATIONS
void sortById() {
    clearScreen();
    printTitle("SORT BY ID");
    
    printf("\n\t1. Ascending Order\n");
    printf("\t2. Descending Order\n");
    printf("\n\tChoice: ");
    
    int order;
    scanf("%d", &order);
    while (getchar() != '\n');
    
    // Bubble Sort
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            int condition = (order == 1) ? 
                           (students[j].id > students[j + 1].id) :
                           (students[j].id < students[j + 1].id);
            
            if (condition && students[j].isActive && students[j + 1].isActive) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf("\n\t>>> Students sorted by ID!\n");
    pause();
    viewAllStudents();
}

void sortByName() {
    clearScreen();
    printTitle("SORT BY NAME");
    
    printf("\n\t1. Ascending Order (A-Z)\n");
    printf("\t2. Descending Order (Z-A)\n");
    printf("\n\tChoice: ");
    
    int order;
    scanf("%d", &order);
    while (getchar() != '\n');
    
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (!students[j].isActive || !students[j + 1].isActive) continue;
            
            int cmp = strcmp(students[j].name, students[j + 1].name);
            int condition = (order == 1) ? (cmp > 0) : (cmp < 0);
            
            if (condition) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf("\n\t>>> Students sorted by name!\n");
    pause();
    viewAllStudents();
}

void sortByCGPA() {
    clearScreen();
    printTitle("SORT BY CGPA");
    
    printf("\n\t1. Ascending Order (Low to High)\n");
    printf("\t2. Descending Order (High to Low)\n");
    printf("\n\tChoice: ");
    
    int order;
    scanf("%d", &order);
    while (getchar() != '\n');
    
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (!students[j].isActive || !students[j + 1].isActive) continue;
            
            int condition = (order == 1) ? 
                           (students[j].cgpa > students[j + 1].cgpa) :
                           (students[j].cgpa < students[j + 1].cgpa);
            
            if (condition) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf("\n\t>>> Students sorted by CGPA!\n");
    pause();
    viewAllStudents();
}

void sortByDepartment() {
    clearScreen();
    printTitle("SORT BY DEPARTMENT");
    
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (!students[j].isActive || !students[j + 1].isActive) continue;
            
            if (strcmp(students[j].department, students[j + 1].department) > 0) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf("\n\t>>> Students sorted by department!\n");
    pause();
    viewAllStudents();
}

//  STATISTICS AND REPORTS
void displayStatistics() {
    clearScreen();
    printTitle("STATISTICS");
    
    if (studentCount == 0) {
        printf("\n\tNo data available.\n");
        pause();
        return;
    }
    
    int activeCount = 0;
    float totalCGPA = 0.0, maxCGPA = 0.0, minCGPA = 4.0;
    int deptCount[10] = {0};
    char departments[10][30];
    int uniqueDepts = 0;
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            activeCount++;
            totalCGPA += students[i].cgpa;
            
            if (students[i].cgpa > maxCGPA) maxCGPA = students[i].cgpa;
            if (students[i].cgpa < minCGPA) minCGPA = students[i].cgpa;
            
            // Count departments
            int found = 0;
            for (int j = 0; j < uniqueDepts; j++) {
                if (strcmp(departments[j], students[i].department) == 0) {
                    deptCount[j]++;
                    found = 1;
                    break;
                }
            }
            
            if (!found && uniqueDepts < 10) {
                strcpy(departments[uniqueDepts], students[i].department);
                deptCount[uniqueDepts] = 1;
                uniqueDepts++;
            }
        }
    }
    
    printf("\n\t========================================================\n");
    printf("\t            OVERALL STATISTICS\n");
    printf("\t========================================================\n");
    
    printf("\n\tTotal Students:      %d\n", activeCount);
    printf("\tAverage CGPA:        %.2f\n", activeCount > 0 ? totalCGPA / activeCount : 0);
    printf("\tHighest CGPA:        %.2f\n", maxCGPA);
    printf("\tLowest CGPA:         %.2f\n", minCGPA);
    printf("\tTotal Departments:   %d\n", uniqueDepts);
    
    printf("\n\t========================================================\n");
    printf("\t         DEPARTMENT-WISE DISTRIBUTION\n");
    printf("\t========================================================\n");
    
    for (int i = 0; i < uniqueDepts; i++) {
        printf("\n\t%-25s: %d students\n", departments[i], deptCount[i]);
    }
    
    pause();
}

void generateDepartmentReport() {
    clearScreen();
    printTitle("DEPARTMENT-WISE REPORT");
    
    char dept[30];
    printf("\n\tEnter department name: ");
    fgets(dept, 30, stdin);
    trim(dept);
    
    int count = 0;
    float totalCGPA = 0.0;
    float maxCGPA = 0.0, minCGPA = 4.0;
    
    printf("\n\t%-5s %-20s %-8s %-6s\n",
           "ID", "Name", "Semester", "CGPA");
    printLine();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && strcasecmp(students[i].department, dept) == 0) {
            printf("\t%-5d %-20s %-8d %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].semester,
                   students[i].cgpa);
            
            count++;
            totalCGPA += students[i].cgpa;
            if (students[i].cgpa > maxCGPA) maxCGPA = students[i].cgpa;
            if (students[i].cgpa < minCGPA) minCGPA = students[i].cgpa;
        }
    }
    
    if (count > 0) {
        printf("\n\t========================================================\n");
        printf("\t  Total Students:    %d\n", count);
        printf("\t  Average CGPA:      %.2f\n", totalCGPA / count);
        printf("\t  Highest CGPA:      %.2f\n", maxCGPA);
        printf("\t  Lowest CGPA:       %.2f\n", minCGPA);
        printf("\t========================================================\n");
    } else {
        printf("\n\tNo students found in this department.\n");
    }
    
    pause();
}

void generateCGPAReport() {
    clearScreen();
    printTitle("CGPA DISTRIBUTION REPORT");
    
    int excellent = 0, good = 0, average = 0, poor = 0, fail = 0;
    
    for (int i = 0; i < studentCount; i++) {
        if (!students[i].isActive) continue;
        
        if (students[i].cgpa >= 3.5) excellent++;
        else if (students[i].cgpa >= 3.0) good++;
        else if (students[i].cgpa >= 2.5) average++;
        else if (students[i].cgpa >= 2.0) poor++;
        else fail++;
    }
    
    printf("\n\t========================================================\n");
    printf("\t           CGPA DISTRIBUTION\n");
    printf("\t========================================================\n");
    
    printf("\n\tExcellent (3.5 - 4.0):  %d students\n", excellent);
    printf("\tGood (3.0 - 3.49):      %d students\n", good);
    printf("\tAverage (2.5 - 2.99):   %d students\n", average);
    printf("\tPoor (2.0 - 2.49):      %d students\n", poor);
    printf("\tFailing (< 2.0):        %d students\n", fail);
    
    printf("\n\t========================================================\n");
    
    pause();
}

void generateToppersList() {
    clearScreen();
    printTitle("TOP 10 STUDENTS");
    
    // Create a sorted copy
    Student sortedStudents[MAX_STUDENTS];
    int activeCount = 0;
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            sortedStudents[activeCount++] = students[i];
        }
    }
    
    // Sort by CGPA (descending)
    for (int i = 0; i < activeCount - 1; i++) {
        for (int j = 0; j < activeCount - i - 1; j++) {
            if (sortedStudents[j].cgpa < sortedStudents[j + 1].cgpa) {
                Student temp = sortedStudents[j];
                sortedStudents[j] = sortedStudents[j + 1];
                sortedStudents[j + 1] = temp;
            }
        }
    }
    
    int displayCount = (activeCount < 10) ? activeCount : 10;
    
    printf("\n\t%-5s %-20s %-15s %-6s\n",
           "Rank", "Name", "Department", "CGPA");
    printLine();
    
    for (int i = 0; i < displayCount; i++) {
        printf("\t%-5d %-20s %-15s %.2f\n",
               i + 1,
               sortedStudents[i].name,
               sortedStudents[i].department,
               sortedStudents[i].cgpa);
    }
    
    pause();
}

void generateFailingStudents() {
    clearScreen();
    printTitle("FAILING STUDENTS (CGPA < 2.0)");
    
    int count = 0;
    
    printf("\n\t%-5s %-20s %-15s %-8s %-6s\n",
           "ID", "Name", "Department", "Semester", "CGPA");
    printLine();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].cgpa < 2.0) {
            printf("\t%-5d %-20s %-15s %-8d %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].department,
                   students[i].semester,
                   students[i].cgpa);
            count++;
        }
    }
    
    if (count == 0) {
        printf("\n\tNo failing students! All students are performing well.\n");
    } else {
        printf("\n\tTotal failing students: %d\n", count);
    }
    
    pause();
}

void exportToCSV() {
    clearScreen();
    printTitle("EXPORT TO CSV");
    
    FILE* file = fopen("students_export.csv", "w");
    
    if (file == NULL) {
        printf("\n\tError creating CSV file!\n");
        pause();
        return;
    }
    
    // Write header
    fprintf(file, "ID,Name,Age,Email,Phone,Department,Semester,CGPA,Enrollment_Date\n");
    
    // Write data
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            fprintf(file, "%d,%s,%d,%s,%s,%s,%d,%.2f,%s\n",
                    students[i].id,
                    students[i].name,
                    students[i].age,
                    students[i].email,
                    students[i].phone,
                    students[i].department,
                    students[i].semester,
                    students[i].cgpa,
                    students[i].enrollmentDate);
        }
    }
    
    fclose(file);
    
    printf("\n\t>>> Data exported successfully to 'students_export.csv'!\n");
    pause();
}

// FILE OPERATIONS
void saveToFile() {
    FILE* file = fopen(FILENAME, "wb");
    
    if (file == NULL) {
        printf("\n\tError saving data!\n");
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(&nextId, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    
    fclose(file);
}

void loadFromFile() {
    FILE* file = fopen(FILENAME, "rb");
    
    if (file == NULL) {
        return; // File doesn't exist yet
    }
    
    fread(&studentCount, sizeof(int), 1, file);
    fread(&nextId, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    
    fclose(file);
}

void createBackup() {
    clearScreen();
    printTitle("CREATE BACKUP");
    
    FILE* source = fopen(FILENAME, "rb");
    FILE* dest = fopen("students_backup.dat", "wb");
    
    if (source == NULL || dest == NULL) {
        printf("\n\tError creating backup!\n");
        if (source) fclose(source);
        if (dest) fclose(dest);
        pause();
        return;
    }
    
    char buffer[1024];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    
    fclose(source);
    fclose(dest);
    
    printf("\n\t>>> Backup created successfully!\n");
    printf("\tBackup file: students_backup.dat\n");
    pause();
}

void restoreFromBackup() {
    clearScreen();
    printTitle("RESTORE FROM BACKUP");
    
    printf("\n\tWarning: This will replace current data with backup data.\n");
    printf("\tAre you sure? (y/n): ");
    
    char confirm;
    scanf(" %c", &confirm);
    while (getchar() != '\n');
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("\n\tRestore cancelled.\n");
        pause();
        return;
    }
    
    FILE* source = fopen("students_backup.dat", "rb");
    FILE* dest = fopen(FILENAME, "wb");
    
    if (source == NULL || dest == NULL) {
        printf("\n\tError restoring backup!\n");
        if (source) fclose(source);
        if (dest) fclose(dest);
        pause();
        return;
    }
    
    char buffer[1024];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    
    fclose(source);
    fclose(dest);
    
    loadFromFile();
    
    printf("\n\t>>> Backup restored successfully!\n");
    pause();
}

//   UTILITY FUNCTIONS
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    printf("\n\tPress Enter to continue...");
    getchar();
}

void printLine() {
    printf("\t--------------------------------------------------------\n");
}

void printTitle(const char* title) {
    printf("\n\t========================================================\n");
    printf("\t          %s\n", title);
    printf("\t========================================================\n");
}

int isValidEmail(const char* email) {
    int atCount = 0, dotCount = 0;
    int len = strlen(email);
    
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') atCount++;
        if (email[i] == '.') dotCount++;
    }
    
    return (atCount == 1 && dotCount >= 1);
}

int findStudentById(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id && students[i].isActive) {
            return i;
        }
    }
    return -1;
}

void getCurrentDate(char* date) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(date, 20, "%Y-%m-%d", t);
}

void trim(char* str) {
    int len = strlen(str);
    
    // Remove trailing whitespace
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r' || 
           str[len - 1] == ' ' || str[len - 1] == '\t')) {
        str[len - 1] = '\0';
        len--;
    }
    
    // Remove leading whitespace
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t') {
        start++;
    }
    
    if (start > 0) {
        int i;
        for (i = 0; str[start + i] != '\0'; i++) {
            str[i] = str[start + i];
        }
        str[i] = '\0';
    }
}
