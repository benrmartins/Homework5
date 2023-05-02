// Benjamin Martins
// 4/30/23

// The first function I created was the delete_contact. created a user to input of the name the contact the
// user wants to delete.  Then I created a temporary file to store all information expect the one being deleted.
// I used a while loop through all the rows in the structure. Then I checked if the name in the file is not the
// same as the name input, then it adds information to the temporary file in the if statement.
// For the input function I had to loop through the file like in program1. Then I created a structure to add data into
// Lasty I can add the contact number and name to the struct.

// I had a hard time trying to figure out how to delete a contact. I realized there is no function that can delete from the
// file, so I research that you can copy the file into a new file with all the data you want in the old file except the
// data you want to delete


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024


struct phonebook
{
    char name[20];
    char number[10];
};


FILE *phonebook_file() {
    FILE *fptr;
    if ((fptr = fopen("phonebook.bin", "ab+")) == NULL) {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    return fptr;
}

void add_contact(FILE *fptr) {
    struct phonebook contact;
    printf("Enter name: ");
    scanf("%s", contact.name);
    printf("Enter number: ");
    scanf("%s", contact.number);
    fwrite(&contact, sizeof(struct phonebook), 1, fptr);
    printf("Contact added successfully\n");
}

void delete_contact(FILE *fptr) {

    char name[1000];
    char line[1000];
    // allows user to input the name of contact they want to delete
    printf("Enter name: ");
    scanf("%s", name);

    // checks if they can open file or not
    if (fptr == NULL) {
        printf("Cannot open file");
        return;
    }


    // creates a temporary file to store all information expect the one being deleted
    FILE *temp_file = fopen("temp.phonebook.bin", "w");

    // loops through all the rows in the structure
    while (fgets(line, sizeof(line), fptr) != NULL) {
        char *token = strtok(line, ",");
        // checks if the name in the file is not the same as the name input
        if (strcmp(token, name) != 0) {
            // adds information to the temporary file
            fputs(line, temp_file);
        }
    }

    // closes the files
    fclose(fptr);
    fclose(temp_file);

    // remove the old file
    remove("phonebook.bin");
    // replace old file with new file
    rename("temp.phonebook.bin", "phonebook.bin");

    printf("Successfully deleted contact information\n");


}

void search_contact(FILE *fptr) {
    struct phonebook contact;
    char name[20];
    printf("Enter name: ");
    scanf("%s", name);
    rewind(fptr);
    while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1) {
        if (strcmp(contact.name, name) == 0) {
            printf("Number: %s\n", contact.number);
            return;
        }
    }
    printf("Contact not found.\n");
}

void list_contacts(FILE *fptr) {
    struct phonebook contact;
    rewind(fptr);
    printf("Lisiting contacts:\n");
    while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1)
    {
        printf("Name: %s\tNumber: %s\n", contact.name, contact.number);
    }
}

void Import(FILE *fptr) {
    // used to through the number of rows in a file
    char line[MAX_LINE];

    // loops through the file like in program1
    while (fgets(line, MAX_LINE, fptr)) {
        // creates a structure to add data into
        struct phonebook contact;
        char *token = strtok(line, ",");
        // adds the contact name to the struct
        strcpy(contact.name, token);
        token = strtok(NULL, ",");
        // adds the contact number to the struct
        strcpy(contact.number, token);
    }

    fclose(fptr);

    printf("Successfully imported the contact information\n");


}

void Export(FILE *fptr) {
    struct phonebook contact;

    // opens the old file to write in it
    fptr = fopen("phonebook.bin", "w");
    // checks if the file can be opened
    if (fptr == NULL) {
        printf("Cannot open file");
        return;
    }

    // loops through the structure phonebook
    while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1) {
        // adds all data into the phonebook from the structure
        fprintf(fptr, "%s,%s\n", contact.name, contact.number);
    }

    printf("Successfully exported the contact information to file\n");

    fclose(fptr);

}

int main() {
    // open the phonebook file
    FILE *fptr = phonebook_file();

    while (1)
    {
        int choice;
        printf("---------MENU---------\n");
        printf("1. Add contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Import from CSV\n");
        printf("6. Export to CSV\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("----------------------\n");
        switch (choice)
        {
            case 1:
                add_contact(fptr);
                break;
            case 2:
                delete_contact(fptr);
                break;
            case 3:
                search_contact(fptr);
                break;
            case 4:
                list_contacts(fptr);
                break;
            case 5:
                Import(fptr);
                break;
            case 6:
                Export(fptr);
                break;
            case 7:
                fclose(fptr);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

}