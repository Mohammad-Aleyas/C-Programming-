#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

Book books[MAX_BOOKS];
Member members[MAX_MEMBERS];
IssueRecord issues[MAX_ISSUES];

int book_count = 0;
int member_count = 0;
int issue_count = 0;

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

int findBookIndex(const char *book_id) {
    for (int i = 0; i < book_count; i++) {
        if (strcmp(books[i].id, book_id) == 0) {
            return i;
        }
    }
    return -1;
}

int findMemberIndex(const char *member_id) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].id, member_id) == 0) {
            return i;
        }
    }
    return -1;
}

void seedDefaultData(void) {
    /* Pre-populates initial sample records if no .dat files exist yet */
    book_count = 4;
    strcpy(books[0].id, "B101");
    strcpy(books[0].title, "C Programming Language");
    strcpy(books[0].author, "Dennis Ritchie");
    strcpy(books[0].category, "Computer Science");
    books[0].total_qty = 5;
    books[0].available_qty = 4;

    strcpy(books[1].id, "B102");
    strcpy(books[1].title, "Data Structures & Algorithms");
    strcpy(books[1].author, "Mark Allen");
    strcpy(books[1].category, "Computer Science");
    books[1].total_qty = 4;
    books[1].available_qty = 4;

    strcpy(books[2].id, "B103");
    strcpy(books[2].title, "Engineering Mathematics");
    strcpy(books[2].author, "B.S. Grewal");
    strcpy(books[2].category, "Mathematics");
    books[2].total_qty = 6;
    books[2].available_qty = 6;

    strcpy(books[3].id, "B104");
    strcpy(books[3].title, "Digital Logic Design");
    strcpy(books[3].author, "Morris Mano");
    strcpy(books[3].category, "Electronics");
    books[3].total_qty = 3;
    books[3].available_qty = 2;

    member_count = 3;
    strcpy(members[0].id, "M201");
    strcpy(members[0].name, "Mohammad Aleyas");
    strcpy(members[0].department, "Computer Science & Engineering");
    strcpy(members[0].contact, "+91 9876543210");

    strcpy(members[1].id, "M202");
    strcpy(members[1].name, "K. Santhosh Kumar");
    strcpy(members[1].department, "Information Technology");
    strcpy(members[1].contact, "+91 9123456789");

    strcpy(members[2].id, "M203");
    strcpy(members[2].name, "B. Mahesh Kumar");
    strcpy(members[2].department, "Electronics & Communication");
    strcpy(members[2].contact, "+91 9988776655");

    issue_count = 2;
    strcpy(issues[0].txn_id, "TXN-901");
    strcpy(issues[0].book_id, "B101");
    strcpy(issues[0].book_title, "C Programming Language");
    strcpy(issues[0].member_id, "M202");
    strcpy(issues[0].member_name, "K. Santhosh Kumar");
    issues[0].issue_days = 14;
    issues[0].overdue_days = 0;
    issues[0].fine_amount = 0;
    issues[0].returned = 0;

    strcpy(issues[1].txn_id, "TXN-902");
    strcpy(issues[1].book_id, "B104");
    strcpy(issues[1].book_title, "Digital Logic Design");
    strcpy(issues[1].member_id, "M203");
    strcpy(issues[1].member_name, "B. Mahesh Kumar");
    issues[1].issue_days = 14;
    issues[1].overdue_days = 3;
    issues[1].fine_amount = 30;
    issues[1].returned = 0;

    saveAllData();
}

void saveAllData(void) {
    FILE *fb = fopen("books.dat", "wb");
    FILE *fm = fopen("members.dat", "wb");
    FILE *fi = fopen("issues.dat", "wb");

    if (fb != NULL) {
        fwrite(&book_count, sizeof(int), 1, fb);
        fwrite(books, sizeof(Book), book_count, fb);
        fclose(fb);
    }
    if (fm != NULL) {
        fwrite(&member_count, sizeof(int), 1, fm);
        fwrite(members, sizeof(Member), member_count, fm);
        fclose(fm);
    }
    if (fi != NULL) {
        fwrite(&issue_count, sizeof(int), 1, fi);
        fwrite(issues, sizeof(IssueRecord), issue_count, fi);
        fclose(fi);
    }
}

void loadAllData(void) {
    FILE *fb = fopen("books.dat", "rb");
    FILE *fm = fopen("members.dat", "rb");
    FILE *fi = fopen("issues.dat", "rb");

    if (fb == NULL && fm == NULL && fi == NULL) {
        seedDefaultData();
        return;
    }

    if (fb != NULL) {
        fread(&book_count, sizeof(int), 1, fb);
        if (book_count > MAX_BOOKS) book_count = MAX_BOOKS;
        fread(books, sizeof(Book), book_count, fb);
        fclose(fb);
    }
    if (fm != NULL) {
        fread(&member_count, sizeof(int), 1, fm);
        if (member_count > MAX_MEMBERS) member_count = MAX_MEMBERS;
        fread(members, sizeof(Member), member_count, fm);
        fclose(fm);
    }
    if (fi != NULL) {
        fread(&issue_count, sizeof(int), 1, fi);
        if (issue_count > MAX_ISSUES) issue_count = MAX_ISSUES;
        fread(issues, sizeof(IssueRecord), issue_count, fi);
        fclose(fi);
    }
}
