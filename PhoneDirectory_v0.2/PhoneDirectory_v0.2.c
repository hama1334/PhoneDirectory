#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef __cplusplus
typedef char bool;
#define TRUE 1
#define FALSE 0
#endif

#define MAXLEN 100
#define ENTRIES 3

struct PhoneDirectoryEntry
{
//So, our PhoneDirectory basically is all about three char arrays. Name, Surname and Phone. Felt that it's better to
//have the phone number as char array rather than an int. Was I right?
	char *name;
	char *surname;
	char *phone;
	struct PhoneDirectoryEntry *next;
	struct PhoneDirectoryEntry *prev;
// My purpose was to experiment with doubly linked lists. Apparently, a binary tree or a cyclic array might been
// better structures for this directory. I shall try both in next version. My vision is to combine a kind of hashtable
// where is table entry will hold a binary tree
};

typedef struct PhoneDirectoryEntry entry;

typedef struct PhoneDirectory
{
	entry *first;
	entry *last;
//	entry *current;
// Wondering if a current pointer would serve any meaningful purpose
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
// It Somehow felt better to use strdup rather than strcpy. Is it?
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

directory * DirectoryInitialize(directory *dir, entry *element)
{
// I made the decision to initialize the directory with its first element, as the implementation was easier.
// That feels however counterintuitive. Why not being able to initialize an 'empty' directory?

	dir = (directory *)malloc(sizeof(directory));

	dir->first = element;
	dir->last = element;
	dir->count = 1;
	element->next = NULL;
	element->prev = NULL;

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
// Follows the strcmp logic. Returns 0 if and only if all elements are identical. It sorts elements first based on surname, then on name,
// and finally on phone number.

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
//	fprintf(stderr, "with arguments %s %s and %s\n", element->name, element->surname, element->phone);

	entry *p, *pprev;

		if (DirectoryIsEmpty(dir))
			return (dir = DirectoryInitialize(dir, element));

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
		return dir;

}

entry *DirectoryFind(directory *dir, char *s)
{
// This version only searches based on surname. It will be extended to also search by name and by phone number

	entry *p;

	if (DirectoryIsEmpty(dir))
	{
		fprintf(stderr, "The PhoneDirectory is empty.\n");
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
// Similarly to DirectoryFind, this version of the EntryDelete function works only by surname. It will be extended
// to also delete based on name and phone number
	entry *p, *q;

	p = DirectoryFind(dir, s);
	if (p == NULL)
	{
		fprintf(stderr, "Cannot delete a non-existing record\n");
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
	}
	else if (p == DirectoryEnd(dir))
	{
		q = p;
		p = p->prev;
		dir->last = p;
		p->next = NULL;
		--(dir->count);
		return dir;
	}
	else
	{
		q = p->prev;
		q->next = p->next;
		p->next->prev = q;
		--(dir->count);
		return dir;
	}
}

void DirectoryPrintToFile(directory *dir, FILE *f)
{
	entry *p;

	p = DirectoryBegin(dir);
	do
		fprintf(f, "%s, %s, %s\n",p->name, p->surname, p->phone);
	while ((p=NextElement(p))!= NULL);
	return;
}

void DirectoryPrint(directory *dir)
{
	entry *p;
	int i=1;

	p = DirectoryBegin(dir);
	do
		fprintf(stdout, "No: %4d Name: %-25s Surname: %-25s Phone: %-25s\n", i++, p->name, p->surname, p->phone);
	while ((p=NextElement(p))!= NULL);
	return;
}

void RequestNewDataEntry(void)
{
// function for UI

	fprintf(stdout,"\n\nThe choices available are the following:\n");
	fprintf(stdout,"A - Add a record, S - Search for a record, D - Delete a record, V - Print the number of the PhoneDirectory records, P - Print the PhoneDirectory, G - Save the PhoneDirectory in datafile and exit and, E - Exit the PhoneDirectory Application\n");
	fprintf(stdout,"Please give your choice: ");
	return;
}

void fgetname(FILE *f, char *s)
{
	int c;
	int i = 0;

	while (!isalnum(c=fgetc(f)))
		if (c=='+')
			s[i++] = c;;
	s[i++] = c;
	while ((c=fgetc(f)) != '\n')
		s[i++]=c;
	s[i]= '\0';

	return;
}


entry *GetNewEntry(int l)
{
// Function for getting a new entry using the UI
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

void FPrintEntry(FILE *f, entry *record)
{
	if (record == NULL)
	{
		fprintf(stderr, "\nCannot print an empty entry\n");
		return;
	}
	else
	{
		fprintf(f,"\nThe person you are looking for is the following:\nName: %23s\tSurname: %20s\tPhone number: %13s\n\n",record->name, record->surname, record->phone);
		return;
	}
}

void InitialMessageToUser()
{
//function to support UI for program initialization

	fprintf(stdout, "Welcome to The PhoneDirectory Application\n");
	fprintf(stdout, "(c) Dimitris Tsingos 2020, email: tsingos@vtrip.net\n\n");
	fprintf(stdout, "The choices available are the following:\n");
	fprintf(stdout, "A - Add a record\n");
	fprintf(stdout, "S - Search for a record\n");
	fprintf(stdout, "D - Delete a record\n");
	fprintf(stdout, "V - Print the number of the PhoneDirectory records\n");
	fprintf(stdout, "P - Print the PhoneDirectory\n\n");
	fprintf(stdout, "E - Exit the PhoneDirectory Application\n");
	fprintf(stdout, "G - Save the PhoneDirectory in datafile and exit\n");
	fprintf(stdout, "Please give your choice: ");
	return;
}

void FreePhoneDirecory(directory *dir)
{
// not sure at all that this function works well. Is there any way to check it?
	entry *temp, *q;

	for(temp = DirectoryBegin(dir);(temp=NextElement(temp))!=NULL;)
	{
		q = temp;
		free(q);
	}
	free(dir);
}


int fgetline(FILE *f, char *line, char **arguments, int len)
{
	int c, i;
	
	i=0;	
	if ((c=fgetc(f)) == EOF)
		return 0;
	while ( c != '\n' && c != EOF )
	{
		line[i++]=c;
		c=fgetc(f);
	}
	line[i] = '\0';
	return i;
}

char *RemoveWhites(char *word)
//simple funtion to remove possible white spaces in the beging of the PhoneDirectory entries
{
	while(*word == ' ')
		word ++;
	return word;	
}

int tokenize(char *line, char **argument, int count, int len)
{
	int c, i, j, k;

	i = j = k = 0;
	while ((c=line[k++])!= '\0')
	{
		if (c != ',') 
			argument[i][j++] = c;
		else 
		{
			argument[i][j] = '\0';
			i++;
			j=0;
		}
	}
	argument[i][j]='\0';
	for (j=0; j < count; j++)
		argument[j] = RemoveWhites(argument[j]);
	return i;
}	

directory *FetchDataFromFile(FILE *f, directory *dir, int len, int count)
{
	char *line;
	char **arguments;
	int i, n, nlines;
	entry *temp;

	nlines =0;		
	line = (char *)malloc(len * sizeof(char));
	arguments = (char **)malloc(count * sizeof(char *));
	for(i=0; i < count; i++)
		arguments[i] = (char *)malloc(len * sizeof(char));
	while ((n = fgetline(f, line, arguments, len)) != 0)
	{
		i = tokenize(line, arguments, count, len);
		if (i > 0)
			temp = EntryInitialize(arguments[0], arguments[1], arguments[2], len);
		dir = DirectoryInsert(dir, temp);
		nlines ++;
	}
	free(line);
	for(i=count; i >= 0; i--)
		free(arguments[i]);
	free(arguments);
	return dir;
}

int main(void)
{
	directory *PhoneBook;
	entry *record;
	char *s;
	int len = MAXLEN;
	int c;
	static bool PhoneBookIsON = FALSE;
	FILE *data;
	int count = ENTRIES;

	data = fopen("datafile", "r");
	if (data == NULL)
	{
		data = fopen("datafile", "w");
		fclose(data);
		data = fopen("datafile", "r");
		if (data == NULL)
		{
			fprintf(stderr, "The data file does not exist or you don't have the right permissions to create it\n");
			return 0;
		}
	}
	PhoneBook = FetchDataFromFile(data, PhoneBook, len, ENTRIES);
	fclose(data);
	if (PhoneBook != NULL)
		PhoneBookIsON = TRUE;

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
				record = GetNewEntry(len);
				PhoneBook = DirectoryInitialize(PhoneBook, record);
				PhoneBookIsON = TRUE;
			}
			else
			{
				record = GetNewEntry(len);
				PhoneBook = DirectoryInsert(PhoneBook, record);
			}
			RequestNewDataEntry();
			continue;
		}
		else if (c == 'S' || c == 's')
		{			
			if (DirectoryIsEmpty(PhoneBook))
			{
				fprintf(stderr, "\nThe PhoneDirectory is empty.\n");
				RequestNewDataEntry();
				continue;
			}
			else
			{
				fprintf(stdout, "Please give the surname of the person you wish to find: ");
				s = (char *)malloc(len*sizeof(char));
				fgetname(stdin, s);
				FPrintEntry(stdout, (record = DirectoryFind(PhoneBook, s)));
				RequestNewDataEntry();
				continue;
			}
		}
		else if (c == 'D' || c == 'd')
		{
			if (DirectoryIsEmpty(PhoneBook))
			{
				fprintf(stderr, "\nThe PhoneDirectory is empty.\n");
				RequestNewDataEntry();
				continue;
			}
			else
			{
				fprintf(stdout, "Please give the surname of the person's entry you wish to delete: ");
				s = (char *)malloc(len*sizeof(char));
				fgetname(stdin, s);
				PhoneBook = EntryDelete(PhoneBook, s);
				RequestNewDataEntry();
				continue;
			}
		}	
		else if (c == 'V' || c == 'v')		
		{
			if (PhoneBookIsON == FALSE || DirectorySize(PhoneBook) == 0)
				fprintf(stdout, "\nThere are not any records in the PhoneDirectory\n");
			else
			{
				fprintf(stdout, "\nThe PhoneDirectory includes %d record(s)\n", DirectorySize(PhoneBook));
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
		else if (c == 'G' || c == 'g')
		{
			fprintf(stderr, "Saving PhoneBook in datafile and exiting.\n");
			data = fopen("datafile", "w");
			DirectoryPrintToFile(PhoneBook, data);
			fclose(data);
			return 0;
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