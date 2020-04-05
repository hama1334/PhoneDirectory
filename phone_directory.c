#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __cplusplus
typedef char bool;
#define TRUE 1
#define FALSE 0
#endif


struct dir_entry
{
	char *name;
	char *surname;
	char *phone;
	struct dir_entry *next;
	struct dir_entry *prev;
};

typedef struct dir_entry entry;

typedef struct directory
{
	entry *first;
	entry *last;
} directory;

void dir_init(directory *dir)
{
	dir->first = NULL; 
	dir->last = NULL;
		
}

bool dir_empty(directory *dir)
{
	return (NULL == dir->first)? TRUE : FALSE;
}

entry *dir_begin(directory *dir)
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
		
	if (dir_empty(dir))
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
	
	if (strcmp(dir->first->surname, element->surname) == 0)
		return dir->first;
	else 
	{
		if (dir->first->next != NULL)
		{
			temp = (directory *)malloc(sizeof(directory));
			temp = dir->first->next;
			return PhoneDirectoryFind(temp, element);
		}
		else
			return NULL;
	}
	
}

int main(void)
{
	directory *phonebook = (directory *)malloc(sizeof(directory));
	entry *record = (entry *)malloc(sizeof(entry));

	printf("Welcome to The PhoneDirectory Application\n");
	printf("(c) Dimitris Tsingos 2020, email: tsingos@vtrip.net\n\n");
	
	dir_init(phonebook);

	printf("The choices available are the following:\n");
	printf("A - Add a record\n");
	printf("B - Search for a record\n\n");
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
			printf("A - Add a record, B - Search for a record, and, E - Exit the PhoneDirectory Application\n");
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
			printf("The person you are looking for is the following:\nName: %s\nSurname: %s\nPhone number: %s\n\nThank you for using the PhoneDirectory Application\n",tempo->name, tempo->surname, tempo->phone);
			free(tempo);
			printf("\n\nThe choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, and, E - Exit the PhoneDirectory Application\n");
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

	while (!dir_empty(phonebook))
	{
		record = phonebook->first;
		phonebook->first = phonebook->first->next;
		free(record);
	}
	
	free(phonebook);

	return 0;
}	
