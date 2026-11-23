#include <stdio.h>
#include "library.h"

extern Book books[MAX_BOOKS];
extern Member members[MAX_MEMBERS];
extern IssueRecord issues[MAX_ISSUES];
extern int book_count;
extern int member_count;
extern int issue_count;

void displayDashboardStats(void) {
    int total_book_copies = 0;
    int active_loans = 0;
    int total_fines = 0;

    for (int i = 0; i < book_count; i++) {
        total_book_copies += books[i].total_qty;
    }
    for (int i = 0; i < issue_count; i++) {
        if (issues[i].returned == 0) {
            active_loans++;
        }
        total_fines += issues[i].fine_amount;
    }

    printf("\n+----------------------------------------------------------------------+\n");
    printf("| TOTAL BOOKS: %-6d | MEMBERS: %-5d | ISSUED: %-5d | FINES: Rs.%-5d |\n",
           total_book_copies, member_count, active_loans, total_fines);
    printf("+----------------------------------------------------------------------+\n");
}

void printCirculationAuditReport(void) {
    displayDashboardStats();
    printf("\n=== COMPLETE CIRCULATION AUDIT LOG ===\n");
    if (issue_count == 0) {
        printf("No transaction records available.\n");
        return;
    }

    printf("%-10s | %-26s | %-20s | %-10s | %-10s\n",
           "Txn ID", "Book Title", "Member Name", "Status", "Fine (Rs)");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < issue_count; i++) {
        printf("%-10s | %-26s | %-20s | %-10s | Rs.%-7d\n",
               issues[i].txn_id, issues[i].book_title, issues[i].member_name,
               issues[i].returned ? "Returned" : "Active", issues[i].fine_amount);
    }
}

void exportAuditReportToTxt(void) {
    FILE *fp = fopen("Library_Audit_Report.txt", "w");
    if (fp == NULL) {
        printf("[Error] Could not create report file.\n");
        return;
    }

    fprintf(fp, "========================================================================\n");
    fprintf(fp, "           LIBRARY MANAGEMENT SYSTEM - AUDIT REPORT (CSA0213)           \n");
    fprintf(fp, "========================================================================\n");
    fprintf(fp, "Guide: Uma Maheswara Rao\n");
    fprintf(fp, "Team : Mohammad Aleyas, K. Santhosh Kumar, B. Mahesh Kumar\n\n");

    fprintf(fp, "%-10s | %-26s | %-20s | %-10s | %-10s\n",
            "Txn ID", "Book Title", "Member Name", "Status", "Fine (Rs)");
    fprintf(fp, "------------------------------------------------------------------------\n");
    for (int i = 0; i < issue_count; i++) {
        fprintf(fp, "%-10s | %-26s | %-20s | %-10s | Rs.%-7d\n",
                issues[i].txn_id, issues[i].book_title, issues[i].member_name,
                issues[i].returned ? "Returned" : "Active", issues[i].fine_amount);
    }
    fclose(fp);
    printf("[Success] Exported printable report to 'Library_Audit_Report.txt'.\n");
}
