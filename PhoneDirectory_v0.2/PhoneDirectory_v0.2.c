#include "PhoneDirectory_v0.2.h"

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
