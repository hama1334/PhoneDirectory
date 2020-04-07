#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __cplusplus
typedef char bool;
#define TRUE 1
#define FALSE 0
#endif


struct PhoneDirectoryEntry
{
	char *name;
	char *surname;
	char *phone;
	struct PhoneDirectoryEntry *next;
	struct PhoneDirectoryEntry *prev;
};

typedef struct PhoneDirectoryEntry entry;

typedef struct PhoneDirectory
{
	entry *first;
	entry *last;
} directory;

void PhoneDirectoryInitialize(directory *dir)
{
	dir->first = NULL; 
	dir->last = NULL;
	
	return;
}

bool PhoneDirectoryIsEmpty(directory *dir)
{
	return (NULL == dir->first)? TRUE : FALSE;
}

entry *PhoneDirectoryBegin(directory *dir)
{
	return dir->first;
}

entry *dir_end(directory *dir)
{
	return dir->last;
}

entry *dir_next(entry *element)
{
	return element->next;
}



void PhoneDirectoryInsert(directory *dir, entry *element)
{
	directory *temp;
	entry *temp_entry;
		
	if (PhoneDirectoryIsEmpty(dir))
	{
		dir->first = element;
		dir->last = element;
	}
	else
	{
		if (strcmp(element->surname, dir->last->surname) >= 0)
		{
			temp_entry = (entry *)malloc(sizeof(entry));
			temp_entry = dir->last;
			dir->last->next = element;
			dir->last = element;
			dir->last->prev = temp_entry;
			element->next = NULL;
		}
		else if (strcmp(element->surname, dir->last->surname) < 0)
		{
			temp = (directory *)malloc(sizeof(directory));
			temp = dir;
			temp->last = dir->last->prev;
			PhoneDirectoryInsert(temp, element);
		}
	}
	
}	

entry *PhoneDirectoryFind(directory *dir, entry *element)
{
	directory *temp;
	temp = (directory *)malloc(sizeof(directory));
	
	if (strcmp(dir->first->surname, element->surname) == 0)
		return dir->first;
	else 
	{
		if (dir->first->next != NULL)
		{
			temp = dir->first->next;
			return PhoneDirectoryFind(temp, element);
		}
		else
			return NULL;
	}
	
}

void PhoneDirectoryPrint(directory *dir)
{
	entry *record;
	int i = 0;
	record = (entry *)malloc(sizeof(entry));
	
	record = PhoneDirectoryBegin(dir);
	
	if (record == NULL)
	{
		printf("The PhoneDirectory is empty\n");
		return;
	}
	
	while (record!=NULL)
	{
		printf("No: %d, Name: %s, Surname: %s, Phone: %s\n", i+1, record->name, record->surname, record->phone);
		++i;
		record = record->next;
	}
	
	return;
}

int main(void)
{
	directory *phonebook = (directory *)malloc(sizeof(directory));
	entry *record = (entry *)malloc(sizeof(entry));

	printf("Welcome to The PhoneDirectory Application\n");
	printf("(c) Dimitris Tsingos 2020, email: tsingos@vtrip.net\n\n");
	
	PhoneDirectoryInitialize(phonebook);

	printf("The choices available are the following:\n");
	printf("A - Add a record\n");
	printf("B - Search for a record\n\n");
	printf("P - Print the PhoneDirectory\n\n");
	printf("E - Exit the PhoneDirectory Application\n\n");
	printf("Please give your choice: ");
	
	int c;

	while ((c=getchar()) != EOF)
	{
		if (c== 'E' || c == 'e')
			break;
		else if (c == 'A' || c == 'a')
		{
			record->name = (char *)malloc(20*sizeof(char));
			printf("Name: ");
			scanf("%s", record->name);

			record->surname = (char *)malloc(20*sizeof(char));
			printf("Surname: ");
			scanf("%s", record->surname);
			
			record->phone = (char *)malloc(20*sizeof(char));
			printf("Phone number (international format): ");
			scanf("%s", record->phone);
			
			PhoneDirectoryInsert(phonebook, record);
			
			printf("\nThe entry has been registered. Thank you for using the PhoneDirectory application!\n");
			printf("\n\nThe choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
			printf("Please give your choice: ");
			
			continue;
		}
		else if (c == 'B' || c == 'b')
		{
			entry *tempo;
			tempo = (entry *)malloc(sizeof(entry));
			printf("Please give the surname of the person you wish to find: ");
			scanf("%s", record->surname);
			tempo = PhoneDirectoryFind(phonebook, record);
			printf("\nThe person you are looking for is the following:\nName: %s\tSurname: %s\tPhone number: %s\n\nThank you for using the PhoneDirectory Application\n",tempo->name, tempo->surname, tempo->phone);
			free(tempo);
			printf("\n\nThe choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
			printf("Please give your choice: ");
			continue;

		}
		else if (c == 'P' || c == 'p')
		{
			PhoneDirectoryPrint(phonebook);
			printf("\n\nThe choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
			printf("Please give your choice: ");
			continue;
		}
		else if (c == '\n' || c == ' ' || c == '\t')
			continue;
		else
		{
			printf("\nYou have not made a valid choice. Kindly select A or B or E\n");
			continue;
		}
	}

	while (!PhoneDirectoryIsEmpty(phonebook))
	{
		record = phonebook->first;
		phonebook->first = phonebook->first->next;
		free(record);
	}
	
	free(phonebook);

	return 0;
	//this is a draft comment
}	
