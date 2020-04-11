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
	fprintf(stdout,"\nA new record has been created.\n");
	return temp;
}

directory * DirectoryInitialize(directory *dir, entry *element)
{
	dir = (directory *)malloc(sizeof(directory));
	dir->first = element;
	dir->last = element;
	element->next = NULL;
	element->prev = NULL;
	fprintf(stdout, "\nThe PhoneDirectory has been initialized and the first entry has been recorded.\n");
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

directory *DirectoryInsert(directory *dir, entry *element)
{
	entry *p, *q;

	if (DirectoryIsEmpty(dir))
	{
	    fprintf(stdout,"\nstarting the add process\n");
		dir->first = element;
		dir->last = element;
		element->prev = NULL;
		element->next = NULL;
		fprintf(stdout,"\nThe entry has been registered. Thank you for using the PhoneDirectory application!\n");
		return dir;
	}
	else
	{
		for(p=DirectoryBegin(dir); p->next != NULL; p=NextElement(p))
            ;
        q=p;
        p->next=element;
        element->next = NULL;
        element->prev = q;
        dir->last = element;
        fprintf(stdout,"\nA new entry has been registered.\n");
        return dir;
    }

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
		return dir;
	}
//	else if (p->next != NULL && p->prev == NULL)
	else if (p == DirectoryBegin(dir))
	{
		q = p->next;
		dir->first = q;
		q->prev = NULL;
		return dir;
//free(p);
	}
//	else if (p->prev != NULL && p->next == NULL)
	else if (p == DirectoryEnd(dir))
	{
		fprintf(stdout, "\nI have found the last element\n");
		q = p;
		p = p->prev;
		dir->last = p;
		p->next = NULL;
		return dir;
		//free(q);
	}
	else
	{
		q = p->prev;
		q->next = p->next;
		p->next->prev = q;
		//free(p);
		return dir;
	}

}

void DirectoryPrint(directory *dir)
{
	entry *p;
	int i=1;

	p = DirectoryBegin(dir);
	do
		fprintf(stdout, "No:%3d,Name:%10s Surname: %15s Phone:%13s\n", i++, p->name, p->surname, p->phone);
	while ((p=NextElement(p))!= NULL);
	return;
}

void RequestNewDataEntry(void)
{
	fprintf(stdout,"\n\nThe choices available are the following:\n");
	fprintf(stdout,"A - Add a record, S - Search for a record, D - Delete a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
	fprintf(stdout,"Please give your choice: ");

	return;

}

entry *GetNewEntry(int l)
{
	entry *temp;
	char *n, *s, *p;

//	temp = (entry *)malloc(sizeof(entry);
	n = (char *)malloc(l*sizeof(char));
	fprintf(stdout,"Name: ");
	fscanf(stdin, "%s", n);

	s = (char *)malloc(l*sizeof(char));
	fprintf(stdout,"Surname: ");
	fscanf(stdin, "%s", s);

	p = (char *)malloc(l*sizeof(char));
	fprintf(stdout,"Phone number (international format): ");
	fscanf(stdin,"%s", p);

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
		fprintf(stdout,"\nThe person you are looking for is the following:\nName: %15s\tSurname: %15s\tPhone number: %13s\n\nThank you for using the PhoneDirectory Application\n",record->name, record->surname, record->phone);
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

	InitialMessageToUser();

	while ((c=getchar()) != EOF)
	{
		if (c== 'E' || c == 'e')
		{
			fprintf(stdout, "\nThank you for using the PhoneDirectory Application.\n");
			break;
		}
		else if (c == 'A' || c == 'a')
		{
			if (DirectoryIsEmpty(PhoneBook))
			{
				record=GetNewEntry(len);
				PhoneBook = DirectoryInitialize(PhoneBook, record);
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
			printf("Please give the surname of the person you wish to find: ");
			s = (char *)malloc(len*sizeof(char));
			fscanf(stdin, "%s", s);
			PrintEntry(record = DirectoryFind(PhoneBook, s));
			RequestNewDataEntry();
			continue;
		}
		else if (c == 'D' || c == 'd')
		{
			printf("Please give the surname of the person's entry you wish to delete: ");
			s = (char *)malloc(len*sizeof(char));
			fscanf(stdin, "%s", s);
			if ((PhoneBook = EntryDelete(PhoneBook, s)) == NULL)
				fprintf(stderr, "\n*** The PhoneDirectory is now empty***\n");
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
