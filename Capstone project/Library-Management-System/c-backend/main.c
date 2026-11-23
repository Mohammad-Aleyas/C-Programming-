#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main(void) {
    int choice;
    loadAllData();

    do {
        printf("\n============================================\n");
        printf("  LIBRARY MANAGEMENT SYSTEM (CSA0213 CORE)  \n");
        printf("============================================\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Register Member\n");
        printf("5. Display All Members\n");
        printf("6. Issue Book\n");
        printf("7. Return Book & Calculate Fine\n");
        printf("8. Print Summary Report\n");
        printf("0. Save & Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = -1;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: registerMember(); break;
            case 5: displayMembers(); break;
            case 6: issueBook(); break;
            case 7: returnBookAndCalculateFine(); break;
            case 8: printReport(); break;
            case 0: saveAllData(); printf("All records saved. Exiting...\n"); break;
            default: printf("Invalid option. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
