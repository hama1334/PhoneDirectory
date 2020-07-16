#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
int count=0;
struct PhoneDirectory *head;


void createPhonebook(){
	head = (struct PhoneDirectory*)malloc(sizeof(struct PhoneDirectory));
	entry *dummy;
	dummy = (struct PhoneDirectoryEntry*)malloc(sizeof(struct PhoneDirectoryEntry));
	dummy->name="0";
	dummy->surname="0";
	dummy->phone="0";
	dummy->next=NULL;
	dummy->prev=NULL;
	head->first = dummy;
	head->count=count;
	count++; 
}


	void print(){
		entry *tmp;
		if(head==NULL){
			printf("Error list is null\n");
		}
		tmp = head->first;
		while(tmp!=NULL){
		printf("Client%d: Name: %s, Surname: %s, Phone: %s\n",count,tmp->name,tmp->surname,tmp->phone);
		count++;
		tmp=tmp->next;
		}
		}


	void insertToPhonebook(char *name, char *surname, char *phone){
		entry *newContact;
		newContact = (struct PhoneDirectoryEntry*)malloc(sizeof(struct PhoneDirectoryEntry));
		if(newContact != NULL) {
			
		newContact->name = name;
		newContact->surname = surname;
		newContact->phone = phone;
			
		newContact->prev=NULL;
		newContact->next=head->first;
			
		head->first->prev=newContact;
		head->first=newContact;
		}
		/*if(head->next==NULL){
			newContact->name = name;
			newContact->surname = surname;
			newContact->phone = phone;
			
			newContact->prev=NULL;
			newContact->next=head->first;
			
			head->first->prev=newContact;
			head->first=newContact;
		}
		else{
			newContact->name = name;
			newContact->surname = surname;
			newContact->phone = phone;
			newContact->next = head;
			newContact->prev = NULL;
			head -> prev = newContact;
			head = newContact;
		}*/

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

/*directory *FetchDataFromFile(FILE *f, directory *dir, int len, int count)
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
*/

/*void DirectoryPrintToFile(directory *dir, FILE *f)
{
	entry *p;

	p = DirectoryBegin(dir);
	do
		fprintf(f, "%s, %s, %s\n",p->name, p->surname, p->phone);
	while ((p=NextElement(p))!= NULL);
	return;
}*/


int main(){
	char *name;
	char *surname;
	char *phone;
	char c;
	InitialMessageToUser();
	createPhonebook();
	FILE *data;
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
	while ((c=getchar()) != EOF)
	{
		if (c== 'E' || c == 'e')
		{
			fprintf(stdout, "\nThank you for using the PhoneDirectory Application.\n");
			return 0;
		}
		else if (c == 'A' || c == 'a')
		{		name=malloc(100);
				scanf("%s",name);
				surname=malloc(100*sizeof(char));
				scanf("%s",surname);
				phone=malloc(100*sizeof(char));
				scanf("%s",phone);
				insertToPhonebook(name,surname,phone);
				print();	
				continue;
				
			}
			
		
		else if (c == 'S' || c == 's')
		{			
			continue;
		}
		else if (c == 'D' || c == 'd')
		{
			
			continue;
		}
		else if (c == 'P' || c == 'p')
		{
			
			break;
		}
		else if (c == 'G' || c == 'g')
		{
			continue;
		}
		else if (c == '\n' || c == ' ' || c == '\t')
			continue;
		else
		{
		    fprintf(stdout, "You have made a wrong choice");
		    continue;
		}
	}
	/*insertToPhonebook("aaa","aaaa","aaaa");
	insertToPhonebook("aaa1","aaaa1","aaaa1");
	insertToPhonebook("aaa2","aaaa2","aaaa2");
		
	print();*/
	//FreePhoneDirecory(PhoneBook);
	return 0;
}
