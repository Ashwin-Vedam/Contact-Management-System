#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
char name[100];
char phoneNumber[20];
struct Contact* next;
};

void addContact(struct Contact** start) {
struct Contact* newContact = (struct Contact*)malloc(sizeof(struct
Contact));
if (newContact == NULL) {
printf("Memory allocation failed.\n");
exit(1);
}
printf("Enter the name: ");
getchar(); // Clear the newline character from the previous input
fgets(newContact->name, 100, stdin);
newContact->name[strcspn(newContact->name, "\n")] = '\0'; // Remove

printf("Enter the phone number: ");
fgets(newContact->phoneNumber, 20, stdin);
newContact->phoneNumber[strcspn(newContact->phoneNumber, "\n")] =
'\0'; // Remove trailing newline

newContact->next = (*start)->next;
(*start)->next = newContact;
printf("Contact added successfully.\n");
}

void deleteContact(struct Contact* start, const char* name) {
struct Contact* prev = start;
struct Contact* current = start->next;

while (current != NULL) {
if (strcmp(current->name, name) == 0) {
prev->next = current->next;
free(current);
printf("Contact deleted successfully.\n");
return;
}
prev = current;
current = current->next;
}

printf("Contact not found.\n");
}

int countContacts(struct Contact* start) {
int count = 0;
struct Contact* current = start->next;

while (current != NULL) {

count++;
current = current->next;
}

return count;
}

void searchContact(struct Contact* start, const char* name) {
struct Contact* current = start->next;

while (current != NULL) {
if (strcmp(current->name, name) == 0) {
printf("Contact found:\n");
printf("Name: %s\n", current->name);
printf("Phone Number: %s\n", current->phoneNumber);
return;
}
current = current->next;
}

printf("Contact not found.\n");
}

void editContact(struct Contact* start, const char* name) {
struct Contact* current = start->next;

while (current != NULL) {
if (strcmp(current->name, name) == 0) {

printf("Enter the new name: ");
getchar();
fgets(current->name, 100, stdin);
current->name[strcspn(current->name, "\n")] = '\0'; // Remove trailing

printf("Enter the new phone number: ");
fgets(current->phoneNumber, 20, stdin);
current->phoneNumber[strcspn(current->phoneNumber, "\n")] = '\0'; //

printf("Contact edited successfully.\n");
return;
}
current = current->next;
}

printf("Contact not found.\n");
}

void printContacts(struct Contact* start) {
struct Contact* current = start->next;
while (current != NULL) {
printf("Name: %s\n", current->name);
printf("Phone Number: %s\n", current->phoneNumber);
current = current->next;
}
}

int main() {
int choice;
char name[100];
struct Contact* start = (struct Contact*)malloc(sizeof(struct Contact));
if (start == NULL) {
printf("Memory allocation failed.\n");
return 1;
}
start->next = NULL;

printf("** Contact Management System **\n");

do {
printf("\n1. Add Contact\n2. Delete Contact\n3. Count Contacts\n4.Search Contact\n5. Edit Contact\n6. Display Contacts\n7. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
addContact(&start);
break;
case 2:
printf("Enter the name of the contact to delete: ");
getchar();
fgets(name, 100, stdin);
name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
deleteContact(start, name);
break;

case 3:
printf("Total Contacts: %d\n", countContacts(start));
break;
case 4:
printf("Enter the name of the contact to search: ");
getchar();
fgets(name, 100, stdin);
name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
searchContact(start, name);
break;
case 5:
printf("Enter the name of the contact to edit: ");
getchar();
fgets(name, 100, stdin);
name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
editContact(start, name);
break;
case 6:
printf("Contacts:\n");
printContacts(start);
break;
case 7:
printf("Exiting the program.\n");
break;
default:
printf("Invalid choice. Please try again.\n");
}
} while (choice != 7);

// Free the allocated memory for contacts
struct Contact* current = start->next;
while (current != NULL) {
struct Contact* temp = current;
current = current->next;
free(temp);
}
free(start);

return 0;
}