/* Name: Project10_dogs.c
   Purpose: maintains records for canine patients at an animal hospital. Each
   dog's record has a name, breed, patient number, and owner's last name.
   Author: Philip Rosatone */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NAME_LEN 30
struct dog{
	int number;
	char dog_name[NAME_LEN+1];
	char owner_last_name[NAME_LEN+1];
	char breed[NAME_LEN+1];
	struct dog *next;
};

struct dog *append(struct dog *list);
void search(struct dog *list);
void print(struct dog *list);
void clear(struct dog *list);
int read_line(char str[], int n);

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main(void)
{
  char code;

  struct dog *dog_list = NULL;  
  printf("Operation Code: a for appending to the list, s for finding a dog"
	  ", p for printing the list; q for quit.\n");
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    while (getchar() != '\n')   /* skips to end of line */
      ;
    switch (code) {
      case 'a': dog_list = append(dog_list);
                break;
      case 's': search(dog_list);
                break;
      case 'p': print(dog_list);
                break;
      case 'q': clear(dog_list);
		return 0;
      default:  printf("Illegal code\n");
    }
    printf("\n");
  }
}

struct dog *append(struct dog *list)
{
	struct dog *a = 0, *b;
	b = list;
	int add_dog = 1;

	/* Scans in the patient number, name, breed, and owner's last name */
	printf("Patient number: ");
	scanf("%d", &a->number);
	printf("Name: ");
	scanf("%s", &*a->dog_name);
	printf("Breed: ");
        scanf("%s", &*a->breed);
	printf("Owner's last name: ");
	scanf("%s", &*a->owner_last_name);   
	
	/* Checks to see whether the dog has already existed by	patient	number.
           If it does not exist, allocates memory for the dog, stores the data,	
           and appends the dog to the end of the linked	list. Returns the pointer
       	   to the newly	created	dog if the list	is empty. Adds the dog to the end 
       	   of the list and returns the pointer to the linked list otherwise. */
	if(list == '\0')
	{
	   list = a;
	   return list;
	}
	while(list->next != '\0')
	{
	   /* Checks to see whether the dog has already existed by patient number */
	   if(list->number == a->number)
	   {
	      printf("Patient already exists.");
	      add_dog = 0;
	      break;
	   }
	   list = list->next;
	}
	if(add_dog == 1)
	{
	   list->next = a;
	}
	return b;
}

void search (struct dog *list)
{
	char name[NAME_LEN];
	printf("Please enter the dog’s name: ");
	scanf("%s", &*name);

	/* Prints message if dog is not found */
	if(list->dog_name != name)
	{
	   printf("Error, dog could not be found.");
	}
  
	/* Finds the dog by name and prints all of its information */
	while(list->next != '\0')
	{
	   if(list->dog_name == name)
	   {
	      printf("Patient number: %d",list->number);
	      printf("Name: %s",list->dog_name);
	      printf("Owner's last name: %s",list->owner_last_name);   
	      printf("Breed: %s",list->breed);
	      break;
	   }
	   list = list->next;
	}
}

void print(struct dog *list)
{
	/* Prints the name and number of all the dogs */
	while(list->next != '\0')
	{
	   printf("%d", list->number);
 	   printf("%s", list->dog_name);
	   list = list->next;
	}
}

void clear(struct dog *list)
{
	/* Deallocates all memory when user exits the program */
	while(list->next != '\0')
	{
	   struct dog *a;
	   a = list;
	   list = list->next;
	   free(a); /* Deallocates the memory */
	}
}

int read_line(char str[], int n)
{
	int ch, i = 0;

	while (isspace(ch = getchar()));
	   str[i++] = ch;
	   while ((ch = getchar()) != '\n') 
	   {
    	      if (i < n)
	      {
                 str[i++] = ch;
    	      }
	   }
	str[i] = '\0';
	return i;
}
