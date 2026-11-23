#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100
#define MAX_MEMBERS 100
#define MAX_ISSUES 200
#define FINE_PER_DAY 10

typedef struct {
    char id[20];
    char title[100];
    char author[80];
    char category[40];
    int total_qty;
    int available_qty;
} Book;

typedef struct {
    char id[20];
    char name[80];
    char department[60];
    char contact[25];
} Member;

typedef struct {
    char txn_id[25];
    char book_id[20];
    char member_id[20];
    int issue_days;
    int overdue_days;
    int fine_amount;
    int returned;
} IssueRecord;

void clearInputBuffer(void);
void saveAllData(void);
void loadAllData(void);

void addBook(void);
void displayBooks(void);
void searchBook(void);

void registerMember(void);
void displayMembers(void);

void issueBook(void);
void returnBookAndCalculateFine(void);
void printReport(void);

#endif
