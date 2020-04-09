#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PhoneDirectory
{
	char *name;
	char *surname;
	char *phone;
	struct PhoneDirectory *next;
};

typedef struct PhoneDirectory PhoneDirectory;

PhoneDirectory *initialize(char *nam, char *surnam, char *phon)
{
	PhoneDirectory *temp;

	temp = (PhoneDirectory *)malloc(sizeof(PhoneDirectory));
	if (temp == NULL)
	{
		fprintf(stderr, "\n***error: out of memory***\n");
		return NULL;
	}
	else
	{
	    temp->name = (char *)malloc(20*sizeof(char));
	    temp->surname = (char *)malloc(20*sizeof(char));
	    temp->phone = (char *)malloc(20*sizeof(char));
		strcpy(temp->name,nam);
		strcpy(temp->surname, surnam);
		strcpy(temp->phone, phon);
		temp->next = NULL;
		return temp;
	}
}

PhoneDirectory *insert(PhoneDirectory *PhoneBook, char *nam, char *surnam, char *phon)
{
	PhoneDirectory *temp, *p;

	temp = initialize(nam, surnam, phon);
	if (PhoneBook == NULL)
		return temp;
	else
	{
		p = PhoneBook;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
		return PhoneBook;
	}
}

PhoneDirectory * search(PhoneDirectory *PhoneBook, char *s)
{
	PhoneDirectory * temp;

	if (PhoneBook == NULL)
	{
		printf("\n***The PhoneDirectory is empty***\n");
		return NULL;
	}
	else
	{
		for (temp = PhoneBook; temp != NULL; temp = temp->next)
			if (strcmp(temp->surname, s) == 0)
                    return temp;
		return NULL;
	}
}

void print(PhoneDirectory *PhoneBook)
{
	PhoneDirectory * temp;

	if (PhoneBook == NULL)
	{
		printf("\n***The PhoneDirectory is empty***\n");
		return;
	}
	else
	{
		for (temp = PhoneBook; temp != NULL; temp = temp->next)
			printf("Record:= Name: %s, Surname: %s, Phone: %s\n", temp->name, temp->surname, temp->phone);
		return;
	}
}


int main(void)
{
	PhoneDirectory *PhoneBook = initialize("Dimitris", "Tsingos", "+306944563690");
	char *nam = malloc(20*sizeof(char));
	char *surnam = malloc(20*sizeof(char));
	char *phon = malloc(20*sizeof(char));

	printf("Welcome to The PhoneDirectory Application\n");
	printf("(c) Dimitris Tsingos 2020, email: tsingos@vtrip.net\n\n");


	printf("The choices available are the following:\n");
	printf("A - Add a record\n");
	printf("B - Search for a record\n\n");
	printf("P - Print the PhoneDirectory\n\n");
	printf("E - Exit the PhoneDirectory Application\n\n");
	printf("Please give your choice: ");

	int c;

	while ((c=getchar()) != EOF)
	{
		if (c== 'E' || c == 'e')
		{
			free(PhoneBook);
			return 0;
		}
		else if (c == 'A' || c == 'a')
		{
			printf("Name: ");
			scanf("%s", nam);

			printf("Surname: ");
			scanf("%s", surnam);

			printf("Phone number (international format): ");
			scanf("%s", phon);

			PhoneBook = insert(PhoneBook, nam, surnam, phon);

			printf("\nThe entry has been registered. Thank you for using the PhoneDirectory application!\n");
			printf("\n\nThe choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
			printf("Please give your choice: ");

			continue;
		}
		else if (c == 'B' || c == 'b')
		{
			PhoneDirectory *tempo = (PhoneDirectory *)malloc(sizeof(PhoneDirectory));
			printf("Please give the surname of the person you wish to find: ");
			scanf("%s", surnam);
			tempo = search(PhoneBook, surnam);
			printf("\nThe person you are looking for is the following:\nName: %s\tSurname: %s\tPhone number: %s\n\nThank you for using the PhoneDirectory Application\n",tempo->name, tempo->surname, tempo->phone);
			printf("\n\nThe choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
			printf("Please give your choice: ");
			continue;

		}
		else if (c == 'P' || c == 'p')
		{
			print(PhoneBook);
			printf("\n\nThe choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
			printf("Please give your choice: ");
			continue;
		}
		else if (c == '\n' || c == ' ' || c == '\t')
			continue;
		else
		{
			printf("\nYou have not made a valid choice. The choices available are the following:\n");
			printf("A - Add a record, B - Search for a record, P - Print the PhoneDirectory, and, E - Exit the PhoneDirectory Application\n");
			printf("Please give your choice: ");
			continue;
		}
	}

	free(PhoneBook);
	free(tempo);
	free(nam);
	free(surnam);
	free(phon);

	return 0;

}
