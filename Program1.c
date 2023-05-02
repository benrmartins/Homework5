// Benjamin Martins
// 4/28/23

//  First I created an array of the file, so I am able to open it to read the file. Then I checked if the file can be opened.
// Then I Initialize variables like an array to store the rows and total to store the total balance. Then I created a while loop to
// read each row and store it into an array using a token. In that while loop I stored each balance, name and id into the array of structure,
// while keeping track of the number of rows. After that I was able to sort the balances in descending order in the array of structures using a
// nested for loop. Lastly I printed all the information I had using a loop through the first 5 numbers in the sorted array

// A challenge I faced was trying to store the data in the accounts.csv file into a data stucuture. I had to fist figure out that a
// array of structures is the best way to store data from this project. I had a hard time adding the data to the structures. But after looking
// at the sample code from the lectures I was able to figure it out.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

typedef struct Accounts {
    int id;
    char name[100];
    float balance;
} Accounts;


int main(int argc, char *argv[]) {

    // creates a array of the file and opens it to read the file
    char filename[] = "accounts.csv";
    FILE *fp = fopen(filename, "r");

    // checks if the file can be opened
    if (fp == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    printf("Successfully opened file: %s\n", filename);

    // Read the header row
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, fp);

    // Initialize an array to store the rows
    Accounts account[1000];
    int num_rows = 0;
    double total = 0;

    // Read each row and store it in the array
    while (fgets(line, MAX_LINE_SIZE, fp)) {

        char *token;
        // stores each id into the array of structure
        token = strtok(line, ",");
        account[num_rows].id = atoi(token);

        // stores each name into the array of structure
        token = strtok(NULL, ",");
        strncpy(account[num_rows].name, token, sizeof(account[num_rows].name));

        // stores each balance into the array of structure
        token = strtok(NULL, ",");
        token++;
        account[num_rows].balance = atof(token);

        // keeps track of what row the loop is on
        num_rows++;
    }

    // sorts the balances in descending order in the array of structures
    for (int i = 0; i < num_rows - 1; i++) {
        for (int j = i + 1; j < num_rows; j++) {
            if (account[i].balance < account[j].balance) {
                Accounts temp = account[i];
                account[i] = account[j];
                account[j] = temp;
            }
        }
    }

    // gets the total balance in the file
    for(int i = 0; i < num_rows; i++) {
        total = total + account[i].balance;
    }

    // prints out the information
    printf("Total number of accounts: %d\n", num_rows);
    printf("Total balance: $%.2f\n", total);

    printf("\n");

    printf("Top 5 accounts with highest balances:\n");
    // loops through the 5 accounts with the highest balance
    for (int i = 0; i < 5; i++) {
        printf("Account #%s_%d, balance: $%.2f\n", account[i].name, account[i].id, account[i].balance);
    }

    // closes the file
    fclose(fp);

    return 0;

}