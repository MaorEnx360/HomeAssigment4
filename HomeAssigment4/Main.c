#define _CRT_SECURE_NO_WARNINGS
/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/ //uncomment this block to check for heap memory allocation leaks.
// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#define READLINE(STRING,MAX,FILEPTR) fgets((STRING), (MAX), (FILEPTR))
#define SIZEOFSTUDENT(NUMOFCOURSES) ((NUMOFCOURSES)*(2)) + (1)
#define LINE 1023
#define ValidationFactor(factor)  if((factor) > 20 || (factor) < -20){  puts("The Factor is not between -20,20");}  else{
#define AreEqual(a,b) !strcmp(a, b)
#define DEC 10
#define BinStudent 39
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

//axuliry functions
int main()
{
	//Part A
	int* coursesPerStudent = NULL;
	int numberOfStudents = 0;
//	countStudentsAndCourses("studentList.txt", &coursesPerStudent, &numberOfStudents);
	char*** students = makeStudentArrayFromFile("studentList.txt", &coursesPerStudent, &numberOfStudents);
	factorGivenCourse(students, coursesPerStudent, numberOfStudents, "Advanced Topics in C", +5);
	printStudentArray(students, coursesPerStudent, numberOfStudents);
	studentsToFile(students, coursesPerStudent, numberOfStudents); //this frees all memory. Part B fails if this line runs. uncomment for testing (and comment out Part B)

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
		//if (feof(studentCount)) {
			//break;
		//}
		*numberOfStudents += 1;
	}
	rewind(studentCount);
	*coursesPerStudent = (int*)calloc(*numberOfStudents, sizeof(int));
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
	FILE* STUDFIL = fopen(fileName, "r");
	countStudentsAndCourses(fileName, coursesPerStudent, numberOfStudents);
	char*** students = (char***)malloc((*numberOfStudents) * sizeof(char**));
	for (int i = 0; i < *numberOfStudents; i++) {
		int size = SIZEOFSTUDENT(*(*coursesPerStudent + i));
		*(students + i) = (char**)malloc(size * sizeof(char*));
	}
	for (int n = 0; n < *numberOfStudents; n++) {
		char line[LINE];
		int numOfCour = *(*coursesPerStudent + n);
		fgets(line, LINE, STUDFIL);
		char* name = strtok(line, ", |");
		students[n][0] = (char*)malloc(strlen(name) * sizeof(char));
		strcpy(students[n][0], name);
		for (int j = 1; j < SIZEOFSTUDENT(*(*coursesPerStudent + n)); j++) {
			name = strtok(NULL, "|,\n");
			students[n][j] = (char*)malloc(strlen(name) * sizeof(char));
			strcpy(students[n][j], name);
		}
	}
	return students;
}



//add code here



void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor)
{
	ValidationFactor(factor);
	int tmp = 0;
	for (int i = 0; i < numberOfStudents; i++) {
		for (int j = 0; j < coursesPerStudent[i]; j++) {
			if (AreEqual(students[i][j], courseName)) {
				tmp = atoi(students[i][j + 1]);
				tmp += factor;
				_itoa(((tmp > 100) ? 100 : tmp), students[i][j + 1], DEC);
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
	FILE* des = fopen("studentList.txt", "w");
	for (int n = 0; n < numberOfStudents; n++) {
		char line[LINE];
		strcpy(line, students[n][0]);
		strcat(line, "|");
		int max = SIZEOFSTUDENT(*(coursesPerStudent + n));
		for (int j = 1; j < max; j++) {
			strcat(line, students[n][j]);
			if (j % 2 != 0) {
				strcat(line, ",");
			}
			else {
				if (j != max-1) { //don't print '|' in the end
					strcat(line, "|");
				}
			}
		}
		fputs(line, des);
		if (n != numberOfStudents - 1) {
			fputs("\n", des);
		}
		fflush(des);
	}
	for (int n = 0; n < numberOfStudents; n++) {
		free(*(students + n));
	}
	free(students);
	//add code here
}

void writeToBinFile(const char* fileName, Student* students, int numberOfStudents)
{
	FILE* des = fopen(fileName, "wb");
	fwrite(students, sizeof(Student), numberOfStudents,des);
	fflush(des);
	//add code here
}

Student* readFromBinFile(const char* fileName)
{
	FILE* des = fopen(fileName, "rb");
	int n = 0;
	int k = 1;
	Student* arr = NULL;
	while (!feof(des)) {
		arr = (Student*)realloc(arr, k++ * sizeof(Student));
		fread(&arr[n], sizeof(Student), 1, des);
		k++;
		n++;
	}
	return arr;
	//add code here
}

Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents)
{
	Student* arr = (Student*)malloc(numberOfStudents * sizeof(Student));
	for (int n = 0; n < numberOfStudents; n++) {
		strcpy(arr[n].name, students[n][0]);
		int max = SIZEOFSTUDENT(*(coursesPerStudent + n));
		arr[n].grades = (StudentCourseGrade*)malloc((coursesPerStudent[n]) * sizeof(StudentCourseGrade));
		for ( int j = 1, k = 0; j < max; j+=2, k++) {
			strcpy(arr[n].grades[k].courseName, students[n][j]);
			arr[n].grades[k].grade = atoi(students[n][j+1]);
		}
		arr[n].numberOfCourses = (coursesPerStudent[n]);
		}
	return arr;
	//add code here
}

