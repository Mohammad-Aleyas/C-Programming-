#include <stdio.h>
#include <string.h>
#include "library.h"

extern Book books[MAX_BOOKS];
extern Member members[MAX_MEMBERS];
extern IssueRecord issues[MAX_ISSUES];
extern int book_count;
extern int member_count;
extern int issue_count;

int calculateFine(int issue_days, int actual_days) {
    if (actual_days > issue_days) {
        return (actual_days - issue_days) * FINE_PER_DAY;
    }
    return 0;
}

void issueBook(void) {
    if (issue_count >= MAX_ISSUES) {
        printf("[Error] Transaction log capacity reached.\n");
        return;
    }

    char book_id[20], member_id[20];
    int days;

    printf("Enter Book ID to issue: ");
    scanf("%19s", book_id);
    int b_idx = findBookIndex(book_id);
    if (b_idx == -1) {
        printf("[Error] Book ID '%s' not found.\n", book_id);
        return;
    }
    if (books[b_idx].available_qty <= 0) {
        printf("[Error] '%s' has 0 copies available.\n", books[b_idx].title);
        return;
    }

    printf("Enter Member ID: ");
    scanf("%19s", member_id);
    int m_idx = findMemberIndex(member_id);
    if (m_idx == -1) {
        printf("[Error] Member ID '%s' not found.\n", member_id);
        return;
    }

    printf("Enter Loan Duration in Days (default 14): ");
    if (scanf("%d", &days) != 1 || days < 1) {
        clearInputBuffer();
        days = 14;
    }

    IssueRecord rec;
    snprintf(rec.txn_id, sizeof(rec.txn_id), "TXN-%d", 901 + issue_count);
    strcpy(rec.book_id, books[b_idx].id);
    strcpy(rec.book_title, books[b_idx].title);
    strcpy(rec.member_id, members[m_idx].id);
    strcpy(rec.member_name, members[m_idx].name);
    rec.issue_days = days;
    rec.overdue_days = 0;
    rec.fine_amount = 0;
    rec.returned = 0;

    books[b_idx].available_qty -= 1;
    issues[issue_count++] = rec;
    saveAllData();

    printf("[Success] Issued '%s' to %s | Transaction ID: %s (Loan: %d days)\n",
           rec.book_title, rec.member_name, rec.txn_id, rec.issue_days);
}

void displayActiveIssues(void) {
    int count = 0;
    printf("\n%-10s | %-26s | %-20s | %-8s | %-12s\n",
           "Txn ID", "Book Title", "Borrower", "LoanDays", "Est. Fine");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < issue_count; i++) {
        if (issues[i].returned == 0) {
            printf("%-10s | %-26s | %-20s | %-8d | Rs.%-9d\n",
                   issues[i].txn_id, issues[i].book_title,
                   issues[i].member_name, issues[i].issue_days,
                   issues[i].fine_amount);
            count++;
        }
    }
    if (count == 0) {
        printf("No active book loans currently.\n");
    }
}

void returnBookAndCalculateFine(void) {
    char txn_id[25];
    int actual_days;

    displayActiveIssues();
    printf("\nEnter Transaction ID to return (e.g., TXN-901): ");
    scanf("%24s", txn_id);

    for (int i = 0; i < issue_count; i++) {
        if (strcmp(issues[i].txn_id, txn_id) == 0 && issues[i].returned == 0) {
            printf("Allowed Loan Duration: %d days. Enter actual days kept: ", issues[i].issue_days);
            scanf("%d", &actual_days);

            issues[i].overdue_days = (actual_days > issues[i].issue_days)
                                     ? (actual_days - issues[i].issue_days)
                                     : 0;
            issues[i].fine_amount = calculateFine(issues[i].issue_days, actual_days);
            issues[i].returned = 1;

            int b_idx = findBookIndex(issues[i].book_id);
            if (b_idx != -1 && books[b_idx].available_qty < books[b_idx].total_qty) {
                books[b_idx].available_qty += 1;
            }

            saveAllData();
            printf("[Success] Book '%s' returned! Overdue Days: %d | Fine Collected: Rs.%d\n",
                   issues[i].book_title, issues[i].overdue_days, issues[i].fine_amount);
            return;
        }
    }
    printf("[Error] Active transaction '%s' not found.\n", txn_id);
}
