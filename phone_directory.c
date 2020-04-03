#include <stdlib.h>
#include <stdio.h>

typedef struct dir_entry
{
	char *name;
	char *surname;
	char *phone;
	struct dir_entry *next;
	struct dir_entry *prev;
} dir_entry;

typedef struct directory
{
	dir_entry *first;
	dir_entry *last;
} directory;

directory *dir_init(directory *dir)
{
		directory *d;
		
		d = (directory *)malloc(sizeof(directory));
				
		d=dir;
		d->first = d->last = NULL;
		
		return d;
}

directory *insert(directory *dir, dir_entry *entry)
{
/*	directory *d;
	dir_entry *e;
	
	if (dir == NULL)
		d=dir_init(dir);
	if (d->first == d->last)
	{
		e = (dir_entry *)malloc(sizeof(dir_entry));
	} */
}

dir_entry *find(directory *dir, char *argum);

directory *delete(directory *dir, char *argum) ;

int main(void)
{
	directory *dir;

	return 0;
}	
