#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __cplusplus
typedef char bool;
#define TRUE 1
#define FALSE 0
#endif

#define MAXLEN 25

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
	int count;
} directory;

entry *EntryInitialize(char *n, char *s, char *p, int len)
{
	entry *temp;
	temp = (entry *)malloc(sizeof(entry));
	temp->name = (char *)malloc(len*sizeof(char));
	temp->surname = (char *)malloc(len*sizeof(char));
	temp->phone = (char *)malloc(len*sizeof(char));
	temp->name=strdup(n);
	temp->surname=strdup(s);
	temp->phone=strdup(p);
	temp->next = NULL;
	temp->prev = NULL;
//	fprintf(stderr,"\nA new record has been created.\n");
	return temp;
}

directory * DirectoryInitialize(directory *dir, entry *element)
{
	dir = (directory *)malloc(sizeof(directory));
	dir->first = (entry *)malloc(sizeof(entry));
	dir->last = (entry *)malloc(sizeof(entry));
	dir->first = element;
	dir->last = element;
	dir->count = 1;
	element->next = NULL;
	element->prev = NULL;
//	fprintf(stderr, "\nThe PhoneDirectory has been initialized and the first entry has been recorded.\n");
	return dir;
}

bool DirectoryIsEmpty(directory *dir)
{
	return (NULL == dir->first)? TRUE : FALSE;
}

entry *DirectoryBegin(directory *dir)
{
	return dir->first;
}

entry *DirectoryEnd(directory *dir)
{
	return dir->last;
}

int DirectorySize(directory *dir)
{
	if (!DirectoryIsEmpty(dir))
		return dir->count;
	else
		return 0;
}

entry *NextElement(entry *element)
{
	return element->next;
}

entry *PrevElement(entry *element)
{
	return element->prev;
}

int EntryCmp(entry *a, entry *b)
{
	if (strcmp(a->surname, b->surname) < 0)
		return -1;
	else if (strcmp(a->surname, b->surname) > 0)
		return 1;
	else if (strcmp(a->name, b->name) < 0)
		return -1;
	else if (strcmp(a->name, b->name) > 0)
		return 1;
	else if (strcmp(a->phone, b->phone) < 0)
		return -1;
	else if (strcmp(a->phone, b->phone) > 0)
		return 1;
	else 
		return 0;
}

bool EntriesAreIdentical(entry *a, entry *b)
{
	return (EntryCmp(a, b) == 0)? TRUE : FALSE;
}

directory *DirectoryInsert(directory *dir, entry *element)
{
//	fprintf(stderr, "\n***The DirectoryInsert function starts here***\n");
	entry *p, *pprev;
	
		for(p=DirectoryBegin(dir); p != NULL && (EntryCmp(p, element) < 0); pprev = p, p=NextElement(p))
			;
		if (p == DirectoryBegin(dir))
		{
			dir->first=element;
			element->next = p;
			p->prev=element;
			if (dir->count == 1)
				dir->last = p;
			++(dir->count);
			return dir;
		}
		pprev->next = element;
		element->prev = pprev;
		if (p == NULL)
		{	element->next = NULL;
			dir->last = element;
		}
		else 
		{
			element->next = p;
			p->prev=element;
		}
		++(dir->count);
//		fprintf(stderr,"\nA new entry has been registered.\n");
		return dir;
}

entry *DirectoryFind(directory *dir, char *s)
{
	entry *p;

	if (DirectoryIsEmpty(dir))
	{
		fprintf(stderr, "\n***error***: The PhoneDirectory is empty.\n");
		return NULL;
	}
	else
		for(p=DirectoryBegin(dir); p != NULL; p=NextElement(p))
			if (strcmp(p->surname, s) == 0)
				return p;
		return NULL;
}

directory *EntryDelete(directory *dir, char *s)
{

	entry *p, *q;

	p = DirectoryFind(dir, s);

	if (p == NULL)
	{
		fprintf(stderr, "\n***error***Cannot delete a non-existing record\n");
		return dir;
	}
	else if (p == DirectoryBegin(dir) && p == DirectoryEnd(dir))
	{
		dir->first= NULL;
		dir->last= NULL;
		dir->count = 0;
		return dir;
	}
	else if (p == DirectoryBegin(dir))
	{
		q = p->next;
		dir->first = q;
		q->prev = NULL;
		--(dir->count);
		return dir;
// free(p);
	}
	else if (p == DirectoryEnd(dir))
	{
// fprintf(stdout, "\nI have found the last element\n");
		q = p;
		p = p->prev;
		dir->last = p;
		p->next = NULL;
		--(dir->count);
		return dir;
// free(q);
	}
	else
	{
		q = p->prev;
		q->next = p->next;
		p->next->prev = q;
		//free(p);
		--(dir->count);
		return dir;
	}

}

void DirectoryPrint(directory *dir)
{
	entry *p;
	int i=1;

	p = DirectoryBegin(dir);
	do
		fprintf(stdout, "No:%3d Name:%-20s Surname: %-20s Phone:%-20s\n", i++, p->name, p->surname, p->phone);
	while ((p=NextElement(p))!= NULL);
//	while ((p=NextElement(p))!= NULL && --(dir->count));
	return;
}

void RequestNewDataEntry(void)
{
	fprintf(stdout,"\n\nThe choices available are the following:\n");
	fprintf(stdout,"A - Add a record, S - Search for a record, D - Delete a record, V - Print the number of the PhoneDirectory records, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
	fprintf(stdout,"Please give your choice: ");

	return;

}

int IgnoreEmptySpaces(FILE *f)
{
	int c;
	
	c=fgetc(f);
	while (c == '\n' || c == '\t' || c == ' ')
		c=fgetc(f);
	return c;
}

void fgetname(FILE *f, char *s)
{
	int c;
	int i = 1;

	c = IgnoreEmptySpaces(stdin);
	s[0] = c;
	while ((c=fgetc(f)) != '\n')
		s[i++]=c;
	s[i]= '\0';
	
	return;
}

entry *GetNewEntry(int l)
{
	entry *temp;
	char *n, *s, *p;

	n = (char *)malloc(l*sizeof(char));
	fprintf(stdout,"Name: ");
	fgetname(stdin, n);

	s = (char *)malloc(l*sizeof(char));
	fprintf(stdout,"Surname: ");
	fgetname(stdin, s);

	p = (char *)malloc(l*sizeof(char));
	fprintf(stdout,"Phone number (international format): ");
	fgetname(stdin, p);
	
	temp = EntryInitialize(n, s, p, l);

	return temp;
}

void PrintEntry(entry *record)
{
	if (record == NULL)
	{
		fprintf(stderr, "\n***error: Cannot print an empty entry***\n");
		return;
	}
	else
	{
		fprintf(stdout,"\nThe person you are looking for is the following:\nName: %23s\tSurname: %20s\tPhone number: %13s\n\n",record->name, record->surname, record->phone);
		return;
	}
}

void InitialMessageToUser()
{
	fprintf(stdout, "Welcome to The PhoneDirectory Application\n");
	fprintf(stdout, "(c) Dimitris Tsingos 2020, email: tsingos@vtrip.net\n\n");

	fprintf(stdout, "The choices available are the following:\n");
	fprintf(stdout, "A - Add a record\n");
	fprintf(stdout, "S - Search for a record\n");
	fprintf(stdout, "D - Delete a record\n");
	fprintf(stdout, "V - Print the number of the PhoneDirectory records\n");
	fprintf(stdout, "P - Print the PhoneDirectory\n\n");
	fprintf(stdout, "E - Exit the PhoneDirectory Application\n\n");
	fprintf(stdout, "Please give your choice: ");

	return;
}

void FreePhoneDirecory(directory *dir)
{
	entry *temp, *q;

	for(temp = DirectoryBegin(dir);(temp=NextElement(temp))!=NULL;)
	{
		q = temp;
		free(q);
	}
	free(dir);
}


int main(void)
{
	directory *PhoneBook;
	entry *record;
	char *s;
	int len = MAXLEN;
	int c;
	static bool PhoneBookIsON = FALSE;

	InitialMessageToUser();

	while ((c=getchar()) != EOF)
	{
		if (c== 'E' || c == 'e')
		{
			fprintf(stdout, "\nThank you for using the PhoneDirectory Application.\n");
			return 0;
		}
		else if (c == 'A' || c == 'a')
		{
			if (DirectoryIsEmpty(PhoneBook))
			{
				record=GetNewEntry(len);
				PhoneBook = DirectoryInitialize(PhoneBook, record);
				PhoneBookIsON = TRUE;
			}
			else
			{
				record = GetNewEntry(len);
			//	fprintf(stderr,"\n***The DirectoryInsert function is called here***\n");
				PhoneBook = DirectoryInsert(PhoneBook, record);
			}
			RequestNewDataEntry();
			continue;
		}
		else if (c == 'S' || c == 's')
		{
			fprintf(stdout, "Please give the surname of the person you wish to find: ");
			s = (char *)malloc(len*sizeof(char));
			fscanf(stdin, "%s", s);
			PrintEntry(record = DirectoryFind(PhoneBook, s));
			RequestNewDataEntry();
			continue;
		}
		else if (c == 'D' || c == 'd')
		{
			fprintf(stdout, "Please give the surname of the person's entry you wish to delete: ");
			s = (char *)malloc(len*sizeof(char));
			fscanf(stdin, "%s", s);
			if ((PhoneBook = EntryDelete(PhoneBook, s)) == NULL)
				fprintf(stderr, "\n*** The PhoneDirectory is now empty***\n");
			RequestNewDataEntry();
			continue;
		}
		else if (c == 'V' || c == 'v')
		{
			if (PhoneBookIsON == FALSE || PhoneBook->count == 0)
				fprintf(stdout, "\nThere are not any records in the PhoneDirectory\n");
			else
			{
				fprintf(stdout, "\nThe PhoneDirectory includes %d record(s)\n", PhoneBook->count);
				fprintf(stdout, "The first record is %s and the last is %s\n", PhoneBook->first->surname, PhoneBook->last->surname);
			}
			RequestNewDataEntry();
			continue;
		}
		else if (c == 'P' || c == 'p')
		{
			if (DirectoryIsEmpty(PhoneBook))
				fprintf(stderr, "\nThe PhoneDirectory is empty.\n");
			else
				DirectoryPrint(PhoneBook);
			RequestNewDataEntry();
			continue;
		}
		else if (c == '\n' || c == ' ' || c == '\t')
			continue;
		else
		{
		    fprintf(stdout, "You have made a wrong choice");
		    RequestNewDataEntry();
		    continue;
		}
	}

	FreePhoneDirecory(PhoneBook);

	return 0;

}
