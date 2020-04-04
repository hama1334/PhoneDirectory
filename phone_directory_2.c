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

void dir_push_back(directory *dir, entry *element)
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
			dir_push_back(temp, element);
		}
	}
	
}	

entry *entry_pop_front(directory *dir, entry *element)
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
			return entry_pop_front(temp, element);
		}
		else
			return NULL;
	}
	
}

/*
typedef struct
{
	entry header;
	char *name;
	char *surname;
	char *phonenumber;
} record;
*/

int main(void)
{
	directory phonebook;
	
	entry *a = (entry *)malloc(sizeof(entry));
    entry *b = (entry *)malloc(sizeof(entry));
	entry *c = (entry *)malloc(sizeof(entry));

	a->name = "Katerina";
	a->surname = "Kastriti";
	a->phone = "6972781433";

	b->name = "Dimitris";
	b->surname = "Tsingos";
	b->phone = "6944563690";

	c->name = "Starttech";
	c->surname = "Ventures";
	c->phone = "2118001709";


	dir_init(&phonebook);
	dir_push_back(&phonebook, a);
	dir_push_back(&phonebook, b);
	dir_push_back(&phonebook, c);
	
	for (a = (entry *)dir_begin(&phonebook);a ;a=(entry *)dir_next(a))
	{
		printf("Name: %-15s Surname: %-15s Phone number: %-15s\n", a->name, a->surname, a->phone);
	}
/*	while (!dir_empty(&phonebook))
	{
		a = (entry *) entry_pop_front(&phonebook);
		free(a);
	}
*/
	return 0;
	
}

/*


dir_entry *find(directory *dir, char *argum);

directory *delete(directory *dir, char *argum) ;

int main(void)
{
	return 0;
}


		
	
		
		

	*/