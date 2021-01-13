#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
	char *lastName;
	int assignment, finalExam;
	int *quizzes;
	int total;
};

struct Student *ReadData(FILE *in, int *numStudents, int *numQuizzes)
{
	char name[50];
	int wordCount = 0, i, j;
	
	// Read the first line for n and m.
	fscanf(in, "%d %d", numStudents, numQuizzes);

	// Allocate memory for the each Student.
	struct Student *students = (struct Student *) malloc(*numStudents * sizeof(struct Student));

	for (i = 0; i < *numStudents; i++)
	{
		int quizTotal = 0;

		// Allocate memory for the quizzes of the current iteration of the student.
		students[i].quizzes = (int *)malloc(*numQuizzes * sizeof(int));

		// Read last name from input file.
		// Then get the length of the name for dynamic memory allocation.
		fscanf(in, "%s", name);
		wordCount = strlen(name) + 1;
		students[i].lastName = (char *)malloc(wordCount * sizeof(char));
		strcpy(students[i].lastName, name);


		// Read the assignment score from input file.
		fscanf(in, "%d", &students[i].assignment);
		
		for (j = 0; j < *numQuizzes; j++)
		{
			// Read the quizzes into the current student.
			fscanf(in, "%d", &students[i].quizzes[j]);
			quizTotal += students[i].quizzes[j];
		}

		// Read the final exam score.
		fscanf(in, "%d", &students[i].finalExam);

		// Calculate the students total score.
		students[i].total = quizTotal + students[i].assignment + students[i].finalExam;
	}

	return students;
}

// Return the index of the student with the highest total.
int GetBestStudentIndex(struct Student* students, int numStudents)
{
	int i, index;

	for (i = 0; i < numStudents; i++)
	{
		// Compare students total.
		if (students[i].total > students[numStudents - i].total)
			index = i;	
	}

	return index;
}

// Write to the outputFile all the data stored within the best scoring student.
void OutputData(FILE *out,struct Student student, int numQuizzes)
{
	int i;
	fprintf(out, "Name: %s\n", student.lastName);
	fprintf(out, "Assignment: %d\n", student.assignment);
	fprintf(out, "Quiz:");
	for (i = 0; i < numQuizzes; i++)
	{
		fprintf(out, " %d", student.quizzes[i]);
	}
	fprintf(out, "\n");
	fprintf(out, "Final Exam: %d\n", student.finalExam);
	fprintf(out, "Total: %d\n", student.total);
}

// Free allocated memory.
void FreeData(struct Student *students, int numStudents, int numQuizzes)
{
	int i;
	
	// Free the data inside the array of structs.
	for (i = 0; i < numStudents; i++)
	{
		free(students[i].lastName);
		free(students[i].quizzes);
	}

	// Free the structs itself now.
	free(students);
}

int main(int argc, const char* argv[])
{
	// Open input file.
	FILE *inputFile = fopen("inputFile.txt", "r");

	// Open a the specified text file and if not there create it, writing mode.
	FILE *outputFile = fopen("outputFile.txt", "w");

	struct Student *students;
	int numStudents, numQuizzes;

	// If input file fails to open print error message.
	if (inputFile == NULL)
	{
		printf("Error. File is null!");
		exit(1);
	}
	else
	{
		students = ReadData(inputFile, &numStudents, &numQuizzes);
	}

	OutputData(outputFile, students[GetBestStudentIndex(students, numStudents)], numQuizzes);

	FreeData(students, numStudents, numQuizzes);

	fclose(inputFile);
	fclose(outputFile);

	system("pause");
	return 0;
}
