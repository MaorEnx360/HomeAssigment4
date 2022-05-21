#define _CRT_SECURE_NO_WARNINGS
/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/ //uncomment this block to check for heap memory allocation leaks.
// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#define READLINE(STRING,MAX,FILEPTR) fgets((STRING), (MAX), (FILEPTR))
#define SIZEOFSTUDENT(NUMOFCOURSES) ((NUMOFCOURSES)*(2)) + (1)
#define LINE 1023
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


typedef struct StudentCourseGrade
{
	char courseName[35];
	int grade;
}StudentCourseGrade;

typedef struct Student
{
	char name[35];
	StudentCourseGrade* grades; //dynamic array of courses
	int numberOfCourses;
}Student;


//Part A
void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
int countPipes(const char* lineBuffer, int maxCount);
char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents);
void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor);
void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents);

//Part B
Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents);
void writeToBinFile(const char* fileName, Student* students, int numberOfStudents);
Student* readFromBinFile(const char* fileName);

int main()
{
	//Part A
	int coursesPerStudent[1] = {2};
	int numberOfStudents = 1;
	int k = SIZEOFSTUDENT(2);
	//countStudentsAndCourses("studentList.txt", &coursesPerStudent, &numberOfStudents);
	//char*** students = makeStudentArrayFromFile("studentList.txt", &coursesPerStudent, &numberOfStudents);
	const char students[1][5][30] = { "Roa", "Madar" , "100","Advanced Topics in C","100"};

	//*students[1] = { "Roa" }, { "Madar" }, { "100" };
	//*students[2] = { "Roa" }, { "Madar" }, { "100" };

	//{ {{"Roa"},{"Madar"},{"100"},{"Hedva 2"},{"100"}}, {("Maor","Madar","92","Complex equations","87"},{{"student3"},{"C Advanced"},{"75"}} };
	factorGivenCourse(students, coursesPerStudent, numberOfStudents, "Advanced Topics in C", 5);
//	printStudentArray(students, coursesPerStudent, numberOfStudents);
	//studentsToFile(students, coursesPerStudent, numberOfStudents); //this frees all memory. Part B fails if this line runs. uncomment for testing (and comment out Part B)
	
	//Part B
	Student* transformedStudents = transformStudentArray(students, coursesPerStudent, numberOfStudents);
	writeToBinFile("students.bin", transformedStudents, numberOfStudents);
	Student* testReadStudents = readFromBinFile("students.bin");

	//add code to free all arrays of struct Student

	/*_CrtDumpMemoryLeaks();*/ //uncomment this block to check for heap memory allocation leaks.
	// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019

	return 0;
}

void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
	FILE* studentCount = fopen(fileName, "r");
	assert(studentCount);
	char line[100];
	while (!feof(studentCount)) {
		fgets(line, 100, studentCount);
		*numberOfStudents += 1;
	}
	rewind(studentCount);
	*coursesPerStudent = (int*)calloc(*numberOfStudents,sizeof(int));
	assert(coursesPerStudent);
	int i = 0;
	while (!feof(studentCount)) {
		fgets(line, 100, studentCount);
		*(*(coursesPerStudent)+i) = countPipes(line, 100);
		i++;
	}
	fclose(studentCount);
	//add code here
}

int countPipes(const char* lineBuffer, int maxCount)
{
	if (lineBuffer == NULL) {
		return -1;
	}
	if (maxCount <= 0) 
		return 0;
	int counter = 0;
	for (int i = 0; i <= maxCount && lineBuffer[i] != '\0'; i++) {
		if (lineBuffer[i] == '|') counter++;
	}
	return counter;

	//add code here
}

char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
	/*
	char line[LINE];
	

	FILE* STUDFIL = fopen(fileName, "r");
	countStudentsAndCourses(fileName, coursesPerStudent, numberOfStudents);
	char*** students = (char***)malloc(*numberOfStudents * sizeof(char**));
	for (int i = 0; i < *numberOfStudents; i++) {
		int size = SIZEOFSTUDENT(*(*coursesPerStudent + i));
		*(students + i) = (char**)malloc(size * sizeof(char*));
	}
	for (int n = 0; n < *numberOfStudents; n++) {
		int numOfCour = *(*coursesPerStudent + n);
		fgets(line, LINE, STUDFIL);
		char* ptr = strtok(line, "|");
		char** arr;
		arr = (char**)malloc(numOfCour * sizeof(char*));
		for (int i = 0; ptr; i++) {
			arr[i] = ptr;
			ptr = strtok(NULL, "|");
		}
/*
		char** arr2 = (char**)malloc(numOfCour * 2 * sizeof(char*));
		for (int i = 0; i < 1 + (numOfCour * 2); i++) {
			for(int j = 0; arr[j] != '\0' ;j++){
				if (arr[j] == ',') {
					j++;
				arr2[i]

			}*/
		}
	
	

			//add code here
	


void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor)
{
	if ((factor > 20) || (factor < -20)) {
		puts("The Factor is not between -20,20");
	}
	else {
		int tmp = 0;
		for (int i = 0; i < numberOfStudents; i++) {
			for (int j = 0; j < coursesPerStudent[i]; j++) {
				if (strcmp(students[i][j][0], courseName)) {
					tmp = atoi(students[i][j + 1]);
					tmp += factor;
					(tmp > 100) ? tmp : 100;
					students[i][j + 1] = tmp;
				}
			}
		}
	}
}
//add code here				
	
void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents)
{
	for (int i = 0; i < numberOfStudents; i++)
	{
		printf("name: %s\n*********\n", students[i][0]);
		for (int j = 1; j <= 2 * coursesPerStudent[i]; j += 2)
		{
			printf("course: %s\n", students[i][j]);
			printf("grade: %s\n", students[i][j + 1]);
		}
		printf("\n");
	}
}

void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents)
{
	//add code here
}

void writeToBinFile(const char* fileName, Student* students, int numberOfStudents)
{
	//add code here
}

Student* readFromBinFile(const char* fileName)
{
	//add code here
}

Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents)
{
	//add code here
}
