#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main(void) {
    int choice;
    loadAllData();

    do {
        displayDashboardStats();
        printf("  LIBRARY BOOK MANAGEMENT SYSTEM - MAIN MENU (CSA0213 C PROGRAMMING)\n");
        printf("------------------------------------------------------------------------\n");
        printf("  [MODULE 1: BOOK MANAGEMENT]        [MODULE 2: MEMBER DIRECTORY]\n");
        printf("   1. Add New Book                    6. Register New Member\n");
        printf("   2. View All Books                  7. View All Members\n");
        printf("   3. Edit Book Details               8. Edit Member Profile\n");
        printf("   4. Delete Book                     9. Remove Member\n");
        printf("   5. Search / Filter Books          10. Search Member\n");
        printf("------------------------------------------------------------------------\n");
        printf("  [MODULE 3: ISSUE & RETURN]         [MODULE 4: FINES & AUDIT REPORTS]\n");
        printf("  11. Issue Book to Member           14. View Complete Audit Log\n");
        printf("  12. View Active Issued Books       15. Export Audit Report (.txt)\n");
        printf("  13. Return Book & Calculate Fine    0. Save & Exit\n");
        printf("------------------------------------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = -1;
        }

        switch (choice) {
            case 1:  addBook(); break;
            case 2:  displayBooks(); break;
            case 3:  editBook(); break;
            case 4:  deleteBook(); break;
            case 5:  searchAndFilterBooks(); break;
            case 6:  registerMember(); break;
            case 7:  displayMembers(); break;
            case 8:  editMember(); break;
            case 9:  deleteMember(); break;
            case 10: searchMember(); break;
            case 11: issueBook(); break;
            case 12: displayActiveIssues(); break;
            case 13: returnBookAndCalculateFine(); break;
            case 14: printCirculationAuditReport(); break;
            case 15: exportAuditReportToTxt(); break;
            case 0:  saveAllData(); printf("All data saved to .dat files. Exiting...\n"); break;
            default: printf("[Warning] Invalid choice. Enter a number between 0 and 15.\n");
        }
    } while (choice != 0);

    return 0;
}
