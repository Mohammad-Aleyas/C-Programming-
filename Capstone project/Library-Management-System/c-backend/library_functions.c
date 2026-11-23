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

void saveAllData(void) {
    FILE *fb = fopen("books.dat", "wb");
    FILE *fm = fopen("members.dat", "wb");
    FILE *fi = fopen("issues.dat", "wb");

    if (fb) {
        fwrite(&book_count, sizeof(int), 1, fb);
        fwrite(books, sizeof(Book), book_count, fb);
        fclose(fb);
    }
    if (fm) {
        fwrite(&member_count, sizeof(int), 1, fm);
        fwrite(members, sizeof(Member), member_count, fm);
        fclose(fm);
    }
    if (fi) {
        fwrite(&issue_count, sizeof(int), 1, fi);
        fwrite(issues, sizeof(IssueRecord), issue_count, fi);
        fclose(fi);
    }
}

void loadAllData(void) {
    FILE *fb = fopen("books.dat", "rb");
    FILE *fm = fopen("members.dat", "rb");
    FILE *fi = fopen("issues.dat", "rb");

    if (fb) {
        fread(&book_count, sizeof(int), 1, fb);
        if (book_count > MAX_BOOKS) book_count = MAX_BOOKS;
        fread(books, sizeof(Book), book_count, fb);
        fclose(fb);
    }
    if (fm) {
        fread(&member_count, sizeof(int), 1, fm);
        if (member_count > MAX_MEMBERS) member_count = MAX_MEMBERS;
        fread(members, sizeof(Member), member_count, fm);
        fclose(fm);
    }
    if (fi) {
        fread(&issue_count, sizeof(int), 1, fi);
        if (issue_count > MAX_ISSUES) issue_count = MAX_ISSUES;
        fread(issues, sizeof(IssueRecord), issue_count, fi);
        fclose(fi);
    }
}

void addBook(void) {
    if (book_count >= MAX_BOOKS) {
        printf("Book inventory is full.\n");
        return;
    }
    Book b;
    printf("Enter Book ID: ");
    scanf("%19s", b.id);
    clearInputBuffer();

    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter Category: ");
    fgets(b.category, sizeof(b.category), stdin);
    b.category[strcspn(b.category, "\n")] = '\0';

    printf("Enter Total Quantity: ");
    scanf("%d", &b.total_qty);
    b.available_qty = b.total_qty;

    books[book_count++] = b;
    saveAllData();
    printf("Book added successfully.\n");
}

void displayBooks(void) {
    if (book_count == 0) {
        printf("No books found in catalog.\n");
        return;
    }
    printf("\n%-10s %-28s %-20s %-6s %-6s\n", "ID", "Title", "Author", "Total", "Avail");
    for (int i = 0; i < book_count; i++) {
        printf("%-10s %-28s %-20s %-6d %-6d\n",
               books[i].id, books[i].title, books[i].author,
               books[i].total_qty, books[i].available_qty);
    }
}

void searchBook(void) {
    char query[100];
    clearInputBuffer();
    printf("Enter Book ID, Title, or Author to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (strcmp(books[i].id, query) == 0 ||
            strstr(books[i].title, query) != NULL ||
            strstr(books[i].author, query) != NULL) {
            printf("Found: [%s] %s by %s (Available: %d/%d)\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].available_qty, books[i].total_qty);
            found = 1;
        }
    }
    if (!found) printf("No matching book found.\n");
}

void registerMember(void) {
    if (member_count >= MAX_MEMBERS) {
        printf("Member directory is full.\n");
        return;
    }
    Member m;
    printf("Enter Member ID: ");
    scanf("%19s", m.id);
    clearInputBuffer();

    printf("Enter Full Name: ");
    fgets(m.name, sizeof(m.name), stdin);
    m.name[strcspn(m.name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(m.department, sizeof(m.department), stdin);
    m.department[strcspn(m.department, "\n")] = '\0';

    printf("Enter Contact Number: ");
    fgets(m.contact, sizeof(m.contact), stdin);
    m.contact[strcspn(m.contact, "\n")] = '\0';

    members[member_count++] = m;
    saveAllData();
    printf("Member registered successfully.\n");
}

void displayMembers(void) {
    if (member_count == 0) {
        printf("No registered members found.\n");
        return;
    }
    printf("\n%-10s %-24s %-24s %-15s\n", "ID", "Name", "Department", "Contact");
    for (int i = 0; i < member_count; i++) {
        printf("%-10s %-24s %-24s %-15s\n",
               members[i].id, members[i].name,
               members[i].department, members[i].contact);
    }
}

int findBookIndex(const char *book_id) {
    for (int i = 0; i < book_count; i++) {
        if (strcmp(books[i].id, book_id) == 0) return i;
    }
    return -1;
}

int findMemberIndex(const char *member_id) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].id, member_id) == 0) return i;
    }
    return -1;
}

void issueBook(void) {
    if (issue_count >= MAX_ISSUES) {
        printf("Issue log is full.\n");
        return;
    }
    char book_id[20], member_id[20];
    int days;

    printf("Enter Book ID: ");
    scanf("%19s", book_id);
    int b_idx = findBookIndex(book_id);
    if (b_idx == -1) {
        printf("Book ID not found.\n");
        return;
    }
    if (books[b_idx].available_qty <= 0) {
        printf("Book is currently out of stock.\n");
        return;
    }

    printf("Enter Member ID: ");
    scanf("%19s", member_id);
    if (findMemberIndex(member_id) == -1) {
        printf("Member ID not found.\n");
        return;
    }

    printf("Enter Loan Duration (days): ");
    scanf("%d", &days);

    IssueRecord rec;
    snprintf(rec.txn_id, sizeof(rec.txn_id), "TXN-%d", 100 + issue_count + 1);
    strcpy(rec.book_id, book_id);
    strcpy(rec.member_id, member_id);
    rec.issue_days = days;
    rec.overdue_days = 0;
    rec.fine_amount = 0;
    rec.returned = 0;

    books[b_idx].available_qty -= 1;
    issues[issue_count++] = rec;
    saveAllData();
    printf("Issued book under Transaction ID %s.\n", rec.txn_id);
}

void returnBookAndCalculateFine(void) {
    char txn_id[25];
    int actual_days;
    printf("Enter Transaction ID: ");
    scanf("%24s", txn_id);

    for (int i = 0; i < issue_count; i++) {
        if (strcmp(issues[i].txn_id, txn_id) == 0 && issues[i].returned == 0) {
            printf("Enter total days kept: ");
            scanf("%d", &actual_days);

            issues[i].overdue_days = (actual_days > issues[i].issue_days)
                                     ? (actual_days - issues[i].issue_days)
                                     : 0;
            issues[i].fine_amount = issues[i].overdue_days * FINE_PER_DAY;
            issues[i].returned = 1;

            int b_idx = findBookIndex(issues[i].book_id);
            if (b_idx != -1 && books[b_idx].available_qty < books[b_idx].total_qty) {
                books[b_idx].available_qty += 1;
            }

            saveAllData();
            printf("Returned successfully. Overdue days: %d | Fine: Rs.%d\n",
                   issues[i].overdue_days, issues[i].fine_amount);
            return;
        }
    }
    printf("Active transaction not found.\n");
}

void printReport(void) {
    printf("\n=== LIBRARY SUMMARY REPORT ===\n");
    printf("Total Books: %d | Registered Members: %d | Transactions: %d\n",
           book_count, member_count, issue_count);
    for (int i = 0; i < issue_count; i++) {
        printf("[%s] Book: %s | Member: %s | Status: %s | Fine: Rs.%d\n",
               issues[i].txn_id, issues[i].book_id, issues[i].member_id,
               issues[i].returned ? "Returned" : "Active", issues[i].fine_amount);
    }
}
