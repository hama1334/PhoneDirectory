#include "PhoneDirectory_v0.2.h"

void DirectoryPrint(directory *dir)
{
	entry *p;
	int i=1;

	p = DirectoryBegin(dir);
	do
		fprintf(stdout, "No:%3d,Name:%10s Surname: %15s Phone:%13s\n", i++, p->name, p->surname, p->phone);
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
	fprintf(stdout, "V - Print the number of the PhoneDirectory records\n");
	fprintf(stdout, "P - Print the PhoneDirectory\n\n");
	fprintf(stdout, "E - Exit the PhoneDirectory Application\n\n");
	fprintf(stdout, "Please give your choice: ");

	return;
}
