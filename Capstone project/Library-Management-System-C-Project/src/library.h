#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100
#define MAX_MEMBERS 100
#define MAX_ISSUES 200
#define FINE_PER_DAY 10

/* Data Structures matching the 4 System Modules */
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
    char book_title[100];
    char member_id[20];
    char member_name[80];
    int issue_days;
    int overdue_days;
    int fine_amount;
    int returned; /* 0 = Active Loan, 1 = Returned */
} IssueRecord;

/* Utility & File Persistence Functions (storage) */
void clearInputBuffer(void);
void seedDefaultData(void);
void saveAllData(void);
void loadAllData(void);
int findBookIndex(const char *book_id);
int findMemberIndex(const char *member_id);

/* Module 1: Book Inventory Management */
void addBook(void);
void displayBooks(void);
void editBook(void);
void deleteBook(void);
void searchAndFilterBooks(void);

/* Module 2: Library Member Directory */
void registerMember(void);
void displayMembers(void);
void editMember(void);
void deleteMember(void);
void searchMember(void);

/* Module 3: Book Issue & Return Circulation */
void issueBook(void);
void displayActiveIssues(void);
void returnBookAndCalculateFine(void);
int calculateFine(int issue_days, int actual_days);

/* Module 4: Overdue Fines, Dashboard KPIs & Audit Reports */
void displayDashboardStats(void);
void printCirculationAuditReport(void);
void exportAuditReportToTxt(void);

#endif
