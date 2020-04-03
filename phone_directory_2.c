#include <stdio.h>
#include <stdlib.h>

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
	if (dir_empty(dir))
	{
		dir->first = element;
		dir->last = element;
	}
	else
	{
		dir->last->next = element;
		dir->last = element;
	}
	element->next = NULL;
}	

entry *entry_pop_front(directory *dir)
{
	entry *element = dir->first;
	dir->first= dir->first->next;
	return element;
}

typedef struct
{
	entry header;
	char *name;
	char *surname;
	char *phonenumber;
} record;

int main(void)
{
	directory phonebook;
	
	record *a = (record *)malloc(sizeof(record));
    record *b = (record *)malloc(sizeof(record));
	record *c = (record *)malloc(sizeof(record));

	a->name = "Katerina";
	a->surname = "Kastriti";
	a->phonenumber = "6972781433";

	b->name = "Dimitris";
	b->surname = "Tsingos";
	b->phonenumber = "6944563690";

	c->name = "Starttech";
	c->surname = "Ventures";
	c->phonenumber = "2118001709";


	dir_init(&phonebook);
	dir_push_back(&phonebook, &a->header);
	dir_push_back(&phonebook, &b->header);
	dir_push_back(&phonebook, &c->header);
	
	for (a = (record *)dir_begin(&phonebook);a ;a=(record *)dir_next(&a->header))
	{
		printf("Name: %-15s Surname: %-15s Phone number: %-15s\n", a->name, a->surname, a->phonenumber);
	}
	while (!dir_empty(&phonebook))
	{
		a = (record *) entry_pop_front(&phonebook);
		free(a);
	}
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