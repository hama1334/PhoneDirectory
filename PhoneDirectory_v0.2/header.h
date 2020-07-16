#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*Felt better to organise the structs using a header file*/


/*definitions*/
#ifndef __cplusplus
typedef char bool;
#define TRUE 1
#define FALSE 0
#endif

#define MAXLEN 100
#define ENTRIES 3


/*Structs*/
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
//	entry *current;
// Wondering if a current pointer would serve any meaningful purpose
	int count;
} *directory;



/*Functions*/
entry *EntryInitialize(char *n, char *s, char *p, int len);

directory * DirectoryInitialize(directory *dir, entry *element);

int DirectoryIsEmpty(directory *dir);

entry *DirectoryBegin(directory *dir);

entry *DirectoryEnd(directory *dir);

int DirectorySize(directory *dir);

entry *NextElement(entry *element);

entry *PrevElement(entry *element);

int EntryCmp(entry *a, entry *b);

bool EntriesAreIdentical(entry *a, entry *b);

directory *DirectoryInsert(directory *dir, entry *element);

entry *DirectoryFind(directory *dir, char *s);

directory *EntryDelete(directory *dir, char *s);

void DirectoryPrintToFile(directory *dir, FILE *f);

void DirectoryPrint(directory *dir);

void RequestNewDataEntry(void);

void fgetname(FILE *f, char *s);

entry *GetNewEntry(int l);

void FPrintEntry(FILE *f, entry *record);

void InitialMessageToUser();

void FreePhoneDirecory(directory *dir);

int fgetline(FILE *f, char *line, char **arguments, int len);

char *RemoveWhites(char *word);

int tokenize(char *line, char **argument, int count, int len);

directory *FetchDataFromFile(FILE *f, directory *dir, int len, int count);

