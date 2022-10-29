#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)

#define MAX_NAME 30

// global linked list 'list' contains the list of students
struct studentList {
	struct student* student;
	struct studentList* next;
} *list = NULL;				// currently empty list

// structure "student" contains the student's name, id and linked list of courses
struct student {
	char name[MAX_NAME];
	unsigned int id;
	struct course* courses;		// linked list 'courses' contains names of courses
};

//  structure 'course' contains course's name
struct course {
	char name[MAX_NAME];
	struct course* next;
};

void flushStdIn();
void executeAction(char);

void addStudent(char* studentNameInput, unsigned int idInput); 
void displayStudentList(struct studentList* tempList);	     
struct student* searchStudent(char* studentNameInput);	     
void addCourse(char* studentNameInput, char* courseNameInput);
void displayStudentCourseList(struct studentList* tempList);	
void removeStudent(char* studentNameInput);			        

int main()
{
	char selection = 'a';		
	do
	{
		printf("\nCSE240 HW 7,8\n");
		printf("Please enter your selection:\n");
		printf("HW7:\n");
		printf("\t a: add a new student to the list\n");
		printf("\t d: display student list (no courses)\n");
		printf("\t b: search for an student on the list\n");
		printf("\t q: quit\n");
		printf("HW8:\n");
		printf("\t c: add a course of a student\n");
		printf("\t l: display students who has a specific course\n");
		printf("\t r: remove an student\n");
		printf("\t q: quit\n");

		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	char studentNameInput[MAX_NAME], courseNameInput[MAX_NAME];
	unsigned int idInput;
	struct student* searchResult = NULL;

	switch (c)
	{
	case 'a':	// add student
				// input student details from user
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter id: ");
		scanf("%d", &idInput);
		flushStdIn();
		searchStudent(studentNameInput);
		if (searchStudent(studentNameInput) == NULL)
		{
			addStudent(studentNameInput, idInput);
			printf("\nStudent successfully added to the list!\n");
		}
		else
			printf("\nThat student is already on the list!\n");
		break;

	case 'd':		// display the list
		displayStudentList(list);
		break;

	case 'b':		// search for an student on the list
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchStudent(studentNameInput) == NULL)
			printf("\nStudent name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nStudent name exists on the list! \n\n");
		}
		break;

	case 'r':		// remove student
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char
		searchStudent(studentNameInput);
		if (searchStudent(studentNameInput) == NULL)
			printf("\nStudent name does not exist or the list is empty! \n\n");
		else
		{
			removeStudent(studentNameInput);
			printf("\nStudent successfully removed from the list! \n\n");
		}
		break;

	case 'c':		// add course
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchStudent(studentNameInput) == NULL)
			printf("\nStudent name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nPlease enter course's name: ");
			fgets(courseNameInput, sizeof(courseNameInput), stdin);
			courseNameInput[strlen(courseNameInput) - 1] = '\0';	// discard the trailing '\n' char
			addCourse(studentNameInput, courseNameInput);
			printf("\nCourse added! \n\n");
		}
		break;

	case 'l':		// list course's students
		//searchStudent(studentNameInput);
		displayStudentCourseList(list);
		break;

	case 'q':		// quit
		break;

	default: printf("%c is invalid input!\n", c);
	}
}

void addStudent(char* studentNameInput, unsigned int idInput)
{
	struct course* courses = (struct course*)malloc(sizeof(struct course));
	struct student* student = (struct student*)malloc(sizeof(struct student));
	struct studentList* tempList = (struct studentList*)malloc(sizeof(struct studentList));
	// sets student to tempList
	if(tempList==NULL){
		tempList->student = student;
        	strcpy(tempList->student->name, studentNameInput);
        	tempList->student->id = idInput;
        	courses = NULL;
		tempList->next=NULL;
		list = tempList;
	}else{	
		tempList->student = student;
		strcpy(tempList->student->name, studentNameInput);
		tempList->student->id = idInput;
		tempList->student->courses = NULL;
	// sets next as the list since we insert at the head
		tempList->next = list;
		list = tempList;
	}
}
void displayStudentList(struct studentList* tempList)
{
	if(tempList == NULL){
		return;
	}else{	// print the info and call the function again with the next student
		printf("Student Name: %s\n", tempList->student->name);
		printf("Student id: %d\n", tempList->student->id);
		printf("\n");
		displayStudentList(tempList->next);
	}
}

struct student* searchStudent(char* studentNameInput)
{
	struct studentList* tempList = list;			
	// write the code below.
	while(tempList != NULL){
		if(strcmp(tempList->student->name, studentNameInput) == 0){
			return tempList->student;
		}else{
			tempList = tempList->next;
		}
	}
	return NULL;
}

void addCourse(char* studentNameInput, char* courseNameInput)
{	
	struct studentList* tempList = list;		
	struct course* temp = (struct course*)malloc(sizeof(struct course));
	strcpy(temp->name, courseNameInput);
	while(tempList != NULL){
		if(strcmp(tempList->student->name, studentNameInput) == 0){
			 if(tempList->student->courses == NULL){
        	         	tempList->student->courses=temp;
				tempList->student->courses->next = NULL;
				return;
       			 }else{
				struct course* headCourse = tempList->student->courses;
				while(headCourse->next!=NULL){
					headCourse = headCourse->next;
				}
				temp->next = NULL;
				headCourse->next = temp;
				return;
		         }
		}
		tempList = tempList->next;
	}
	
}

void displayStudentCourseList(struct studentList* tempList)
{
	char courseInput[1024];

	printf("Please enter course's name: \n");
	fgets(courseInput, sizeof(courseInput), stdin);
	courseInput[strlen(courseInput) - 1] = '\0';
	//iterates loop 
	while(tempList != NULL){
		struct course* courseList = tempList->student->courses;
		while(courseList != NULL){
			// prints the student information if theyre found
			if(strcmp(courseList->name, courseInput)==0){
				printf("\nStudent Name: %s\n ", tempList->student->name);
				printf("Student ID: %d\n", tempList->student->id);
				fflush(stdout);
			}
			courseList=courseList->next;
		}
		tempList = tempList->next;
	}
}

void removeStudent(char* studentNameInput)
{

	struct studentList* tempList = list;	// work on a copy of 'list'
	struct course* tempCourse;
	struct studentList* head;
	struct course* courses;
	struct studentList* holder;
	// write the code below.
	head = tempList->next;
	holder = tempList;
	// if student is in the first position
	if(strcmp(tempList->student->name, studentNameInput) == 0){
		tempCourse = tempList->student->courses;
                while(tempCourse != NULL){
                        tempCourse = courses->next;
                        free(courses);
                        courses = tempCourse;
                }
		tempList->next = head->next;
		free(tempList);
		tempList = NULL;
		tempList = head;
		list=tempList ;
	}
	// making sure we get first student in list
	holder = tempList;
	// if the student is in the middle of the list
	while(head->next != NULL){
		if(strcmp(head->student->name, studentNameInput) == 0){
			tempList->next = head->next;	
			free(head);
			tempCourse = tempList->student->courses;
	                while(tempCourse != NULL){
        	                tempCourse = courses->next;
                	        free(courses);
                       		courses = tempCourse;
                	}
			head = NULL;
			list = holder;

		}
			tempList = tempList->next;
			head = head->next;
	}
	// if the student is at the end of the list
	if(strcmp(head->student->name, studentNameInput) == 0){
		tempList->next = 0;
		free(head);
		tempCourse = tempList->student->courses;
                while(tempCourse != NULL){
                        tempCourse = courses->next;
                        free(courses);
                        courses = tempCourse;
                }
		head = NULL;
		list = holder;
	}
}
